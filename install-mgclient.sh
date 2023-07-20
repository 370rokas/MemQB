mkdir temp-mgclient
cd temp-mgclient

git clone https://github.com/memgraph/mgclient.git
cd mgclient

mkdir build
cd build
cmake -DBUILD_CPP_BINDINGS=ON ..

make
echo "INSTALLING."
sudo make install

echo "CLEANING UP."
cd ../../../
rm -rf temp-mgclient

echo "DONE!"