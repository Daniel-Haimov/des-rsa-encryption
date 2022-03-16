# Final Project Linux/Unix - encrypt

## Guide
### Flags:
```
    -m, --method)           [des, rsa]
    -o, --option)           [i/init, e/encrypt, d/encrypt]
    -i, --input)            inputPath
    -c, --cipher)           cipherPath
    -r, --result)           resultPath
    -k, --key)              keyPath
    -prk, --privatekey)     privateKeyPath
    -puk, --publickey)      publicKeyPath
    -pq)                    pqPath
```
### Arguments:
```
    for des:
        for encrypt: (inputPath, keyPath, cipherPath)
        for decrypt: (cipherPath, keyPath, resultPath)
    for rsa:
        for init: (privateKeyPath, publicKeyPath, pqPath)
        for encrypt: (inputPath, publicKeyPath, cipherPath)
        for decrypt: (cipherPath, privateKeyPath, pqPath, resultPath)
```