import loopyCryptor
import socket
import time

if __name__ == '__main__':
    HOST = '192.168.1.105'
    PORT = 9006
    token=0

    #TCP link
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind((HOST,PORT))
    print('Listen to the connection from client...')
    sock.listen(5)
    try:
        while (token==0):
            connection, address = sock.accept()

            #Generate RSA Key Pair: Public Key & Private Key.
            RSA_public_key, RSA_private_key = loopyCryptor.generate_RSA_key()
            print ('This RSA Public Key', RSA_public_key)
            print ('This RSA Private Key', RSA_private_key)
            print ('')

            #Send RSA Public Key.
            connection.send(RSA_public_key)
            print("RSA Public Key Sent!")
            print ('')

            #Receive Encrypted AES Secret Key.
            startTime = time.time()
            cipher_AES = connection.recv(1024)
            print("RSA Public Key is received: ", RSA_public_key)
            print ('')

            #Decrypt AES Secret Key by RSA Private Key.AES Secret Key Otained.
            print ('Decrypting cipher of AES key...')
            decrypted_AES = loopyCryptor.RSA_decrypt(cipher_AES,RSA_private_key)
            print ('AES key decrypted: ', decrypted_AES)
            print ('')
            
            #Receive Encrypted Plaintext.
            cipher_text = connection.recv(1024)
            print("Ciphertext Key is received: ", cipher_text)
            print ('')

            #Decrypt Plaintext by Obtained AES Secret Key.Plaintext Key Otained.
            print ('Decrypting ciphertext...')
            decrypted_text = loopyCryptor.AES_decrypt(cipher_text,decrypted_AES)
            print('The transfered plaintext is:\n%s' % decrypted_text)
            ndTime = time.time()
            print("\nRuntime: %f seconds" % (endTime - startTime))
    except KeyboardInterrupt:
        sock.close()
        print("KeyboardInterrupt")
    sys.exit(0)