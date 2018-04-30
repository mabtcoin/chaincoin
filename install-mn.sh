#!/bin/sh
#Version 0.1
#Info: Installs masterbitcoincoind daemon, Masternode based on privkey, and a simple web monitor.
#masterbitcoin Version 0.9.3.3 or above
#Tested OS: Ubuntu 17.04, 16.04, and 14.04

noflags() {
	echo "┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄"
    echo "Usage: install-mn"
    echo "Example: install-mn"
    echo "┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄"
    exit 1
}

message() {
	echo "╒════════════════════════════════════════════════════════════════════════════════>>"
	echo "| $1"
	echo "╘════════════════════════════════════════════<<<"
}

error() {
	message "An error occured, you must fix it to continue!"
	exit 1
}


prepdependencies() { #TODO: add error detection
	message "Installing dependencies..."
	sudo apt-get update
	sudo DEBIAN_FRONTEND=noninteractive apt-get -y -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" dist-upgrade
	sudo apt-get install automake libdb++-dev build-essential libtool autotools-dev autoconf pkg-config libssl-dev libboost-all-dev libminiupnpc-dev git software-properties-common python-software-properties g++ bsdmainutils libevent-dev -y
	sudo add-apt-repository ppa:bitcoin/bitcoin -y
	sudo apt-get update
	sudo apt-get install libdb4.8-dev libdb4.8++-dev -y
	sudo apt-get install dos2unix curl -y
}

createswap() { #TODO: add error detection
	message "Creating 2GB temporary swap file...this may take a few minutes..."
	sudo dd if=/dev/zero of=/swapfile bs=1M count=2000
	sudo mkswap /swapfile
	sudo chown root:root /swapfile
	sudo chmod 0600 /swapfile
	sudo swapon /swapfile

	#make swap permanent
	sudo echo "/swapfile none swap sw 0 0" >> /etc/fstab
}

clonerepo() { #TODO: add error detection
	message "Cloning from github repository..."
  	cd ~/
	git clone https://github.com/mabtcoin/masterbitcoin.git
}

compile() {
	cd masterbitcoin #TODO: squash relative path
	message "Preparing to build..."
	./autogen.sh
	if [ $? -ne 0 ]; then error; fi
    message "Building Dependencies..."
    cd depends
    make HOST=x86_64-pc-linux-gnu
   	if [ $? -ne 0 ]; then error; fi
	pushd $PWD/depends/x86_64-pc-linux-gnu/
	tar -xf $PWD/depends/built/x86_64-pc-linux-gnu/protobuf*.tar.gz
	popd
    cd ..
	message "Configuring build options..."
	CONFIG_SITE=$PWD/depends/x86_64-pc-linux-gnu/share/conifg.site ./configure $1 --disable-tests -prefix=$PWD/depends/x86_64-pc-linux-gnu/
	if [ $? -ne 0 ]; then error; fi
	message "Building Masterbitcoin...this may take a few minutes..."
	make
	if [ $? -ne 0 ]; then error; fi
	message "Installing Masterbitcoin..."
	sudo make install
	if [ $? -ne 0 ]; then error; fi
    sudo cp $PWD/depends/x86_64-pc-linux-gnu/bin/masterbitcoin* /bin
}

createconf() {
	#TODO: Can check for flag and skip this
	#TODO: Random generate the user and password

	message "Creating masterbitcoin.conf..."
	MNPRIVKEY="6FBUPijSGWWDrhbVPDBEoRuJ67WjLDpTEiY1h4wAvexVZH3HnV6"
	CONFDIR=~/.masterbitcoin
	CONFILE=$CONFDIR/masterbitcoin.conf
	if [ ! -d "$CONFDIR" ]; then mkdir $CONFDIR; fi
	if [ $? -ne 0 ]; then error; fi

	mnip=$(curl -s https://api.ipify.org)
	rpcuser=$(date +%s | sha256sum | base64 | head -c 10 ; echo)
	rpcpass=$(openssl rand -base64 32)
	printf "%s\n" "rpcuser=$rpcuser" "rpcpassword=$rpcpass" "rpcallowip=127.0.0.1" "listen=1" "server=1" "daemon=1" "maxconnections=256" "rpcport=12995" "externalip=$mnip" "bind=$mnip" "masternode=1" "masternodeprivkey=$MNPRIVKEY" "masternodeaddr=$mnip:12994" > $CONFILE

        masterbitcoind
        message "Wait 10 seconds for daemon to load..."
        sleep 20s
        MNPRIVKEY=$(masterbitcoin-cli masternode genkey)
	masterbitcoin-cli stop
	message "wait 10 seconds for deamon to stop..."
        sleep 10s
	sudo rm $CONFILE
	message "Updating masterbitcoin.conf..."
        printf "%s\n" "rpcuser=$rpcuser" "rpcpassword=$rpcpass" "rpcallowip=127.0.0.1" "listen=1" "server=1" "daemon=1" "maxconnections=256" "rpcport=12995" "externalip=$mnip" "bind=$mnip" "masternode=1" "masternodeprivkey=$MNPRIVKEY" "masternodeaddr=$mnip:12994" > $CONFILE

}

createhttp() {
	cd ~/
	mkdir web
	cd web
	wget https://raw.githubusercontent.com/chaoabunga/chc-scripts/master/index.html
	wget https://raw.githubusercontent.com/chaoabunga/chc-scripts/master/stats.txt
	(crontab -l 2>/dev/null; echo "* * * * * echo MN Count:  > ~/web/stats.txt; /usr/local/bin/masterbitcoind masternode count >> ~/web/stats.txt; /usr/local/bin/masterbitcoind getinfo >> ~/web/stats.txt") | crontab -
	mnip=$(curl -s https://api.ipify.org)
	sudo python3 -m http.server 8000 --bind $mnip 2>/dev/null &
	echo "Web Server Started!  You can now access your stats page at http://$mnip:8000"
}

success() {
	masterbitcoind
	message "SUCCESS! Your masterbitcoind has started. Masternode.conf setting below..."
	message "MN $mnip:12994 $MNPRIVKEY TXHASH INDEX"
	exit 0
}

install() {
	prepdependencies
	createswap
	clonerepo
	compile $1
	createconf
	success
}

#main
#default to --without-gui
install --without-gui
