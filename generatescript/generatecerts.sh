#!/bin/bash

echo "Part 1 - creation of directories"
touch ~/.rnd
mkdir certificates
cd ~/certificates
mkdir skeleton
cd skeleton
mkdir certs crl newcerts private
touch index.txt
touch index.txt.attr
echo 01 > serial
cp /etc/ssl/openssl.cnf .
# vi skeleton/openssl.cnf
cp ~/openssl.cnf ~/certificates/skeleton/openssl.cnf
read -p "Press enter to continue"
echo ""

echo "Part 2 - creation of Root CA and its keypair"
cd ~/certificates
cp -a skeleton rootca
cd rootca
openssl req -config openssl.cnf -new -x509 -keyout private/cakey.pem -sha1 -newkey rsa:2048 -days 3650 -set_serial 00 -out cacert.pem
read -p "Press enter to continue"
echo ""

echo "Part 3 - creation of user keypair and certificate signing request"
cd ~/certificates
mkdir users
cd ~/certificates/users
openssl req -config ../skeleton/openssl.cnf -new -keyout user1key.pem -sha1 -newkey rsa:2048 -out user1req.pem
read -p "Press enter to continue"
echo ""

echo "Part 4 - sign the user certificate"
cd ~/certificates/rootca
openssl ca -config openssl.cnf -policy policy_anything -out ../users/user1cert.pem -days 3650 -notext -infiles ../users/user1req.pem
read -p "Press enter to continue"
echo ""

echo "Part 5 - verification of the signature"
cd ~/certificates
openssl x509 -in rootca/cacert.pem -noout -pubkey > /tmp/rootcapubkey
openssl x509 -in users/user1cert.pem -noout -text -certopt ca_default -certopt no_validity -certopt no_serial -certopt no_extensions -certopt no_signame -certopt no_subject | grep -v Signature | sed -e "s/://g" | xxd -r -p > /tmp/signature.bin
openssl rsautl -verify -inkey /tmp/rootcapubkey -in /tmp/signature.bin -pubin > /tmp/DEC
openssl asn1parse -inform der -in /tmp/DEC
# cat users/user1cert.pem | grep -A 100 -e "BEGIN CERTIFICATE" | openssl asn1parse -strparse 4 -out /tmp/field2hash -noout
openssl asn1parse -in users/user1cert.pem -strparse 4 -out /tmp/field2hash -noout
openssl dgst -sha1 /tmp/field2hash
read -p "Press enter to continue"
echo ""
