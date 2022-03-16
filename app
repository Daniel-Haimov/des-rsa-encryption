#!/bin/bash

# method option inputPath cipherPath resultPath keyPath privateKeyPath publicKeyPath pqPath

#### DES ####
# ./des/des [e/encrypt] inputs/input.txt inputs/key.txt outputs/cipher.txt
# ./$method/$method $option $inputPath $keyPath $cipherPath

# ./des/des [d/decrypt] outputs/cipher.txt inputs/key.txt outputs/result.txt
# ./$method/$method $option $cipherPath $keyPath $resultPath

#### RSA ####
# ./rsa/rsa [i/init] data/privateKey.txt data/publicKey.txt data/pq.txt
# ./$method/$method $option $privateKeyPath $publicKeyPath $pqPath

# ./rsa/rsa [e/encrypt] inputs/input.txt data/publicKey.txt outputs/cipher.txt
# ./$method/$method $option $inputPath $publicKeyPath $cipherPath

# ./rsa/rsa [d/decrypt] outputs/cipher.txt data/privateKey.txt data/pq.txt outputs/result.txt
# ./$method/$method $option $cipherPath $privateKeyPath $pqPath $resultPath

# flags:
# m, method) des/rsa
# o, option) option(i/init, e/encrypt, d/encrypt)
# i, input) inputPath
# c, cipher) cipherPath
# r, result) resultPath
# ## KEYS ##
# k, key) keyPath
# prk, privatekey - v) privateKeyPath
# puk, publickey - u) publicKeyPath
# pq - q) pqPath

guide='Flags:
    -m, --method)           [des, rsa]
    -o, --option)           [i/init, e/encrypt, d/encrypt]
    -i, --input)            inputPath
    -c, --cipher)           cipherPath
    -r, --result)           resultPath
    -k, --key)              keyPath
    -prk, --privatekey)     privateKeyPath
    -puk, --publickey)      publicKeyPath
    -pq)                    pqPath
Arguments:
    for des:
        for encrypt: (inputPath, keyPath, cipherPath)
        for decrypt: (cipherPath, keyPath, resultPath)
    for rsa:
        for init: (privateKeyPath, publicKeyPath, pqPath)
        for encrypt: (inputPath, publicKeyPath, cipherPath)
        for decrypt: (cipherPath, privateKeyPath, pqPath, resultPath)'

for arg in "$@"; do
  shift
  case "$arg" in
    "--method")                 set -- "$@" "-m" ;;
    "--option")                 set -- "$@" "-o" ;;
    "--input")                  set -- "$@" "-i" ;;
    "--cipher")                 set -- "$@" "-c" ;;
    "--result")                 set -- "$@" "-r" ;;
    "--key")                    set -- "$@" "-k" ;;
    "-prk" | "--privatekey")    set -- "$@" "-v" ;;
    "-puk" | "--publickey")     set -- "$@" "-u" ;;
    "-pq" | "--pq")             set -- "$@" "-q" ;;
    *)                          set -- "$@" "$arg"
  esac
done


while getopts m:o:i:c:r:k:v:u:q: flag
do
    case "${flag}" in
        m) method=${OPTARG};;
        o) option=${OPTARG};;
        i) inputPath=${OPTARG};;
        c) cipherPath=${OPTARG};;
        r) resultPath=${OPTARG};;
        k) keyPath=${OPTARG};;
        v) privateKeyPath=${OPTARG};;
        u) publicKeyPath=${OPTARG};;
        q) pqPath=${OPTARG};;
    esac
done


if [ -z $method ] || [ -z $option ]
then
    echo 'ERR: missing arguments'
    echo "$guide"
    exit -1
fi

if [ $method == 'des' ]
then
    if [ $option == 'e' ] || [ $option == 'encrypt' ]
    then
        ./$method/$method $option $inputPath $keyPath $cipherPath
    elif [ $option == 'd' ] || [ $option == 'decrypt' ]
    then
        ./$method/$method $option $cipherPath $keyPath $resultPath
    else
        echo 'ERR: wrong option'
        echo "$guide"
        exit -1
    fi
elif  [ $method == 'rsa' ]
then
    if [ $option == 'i' ] || [ $option == 'init' ]
    then
        ./$method/$method $option $privateKeyPath $publicKeyPath $pqPath
    elif [ $option == 'e' ] || [ $option == 'encrypt' ]
    then
        ./$method/$method $option $inputPath $publicKeyPath $cipherPath
    elif [ $option == 'd' ] || [ $option == 'decrypt' ]
    then
        ./$method/$method $option $cipherPath $privateKeyPath $pqPath $resultPath
    else
        echo 'ERR: wrong option'
        echo "$guide"
        exit -1
    fi
else
    echo 'ERR: wrong method'
    echo "$guide"
    exit -1
fi

exit 0


