import loopyCryptor
import socket
import time

if __name__ == '__main__':
    server_ip = "192.168.1.105"
    server_port = 9006
    token=0

    # TCP connection to responder B
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setblocking(1)  
    #print('begin connection')
    sock.connect((server_ip, server_port))
    startTime = time.time()
    try:
        while (token==0):
            print('Connection up')
            print ('Connected')
            print ('')

            #Generate AES Security Key.
            AES_key = loopyCryptor.generate_AES_key()
            print("The AES Security Key is: ", AES_key)

            #Plaintext.
            text = 'Kai-Yu Lu 1614649.'
            print("This the plaintext: ", text)
            print ('')


            #Reveive the RSA Public Key.
            RSA_public_key = sock.recv(1024)
            print("The received RSA Public Key is: ", RSA_public_key)
            print ('')

            #Encrypt AES Secret Key by RSA Public Key.
            cipher_AES = loopyCryptor.RSA_encrypt(AES_key,RSA_public_key)    
            print ('This is the encrypted AES security key by RSA Public Key', cipher_AES)
            print ('')

            #Encrypt Plaintext by AES Secret Key.
            cipher_text = loopyCryptor.AES_encrypt(text,AES_key)
            print ('This is the encrypted plainext by AES security key',cipher_text)
            print ('')

            #Send Encrypted AES Secret Key and Plaintext.
            sock.send(cipher_AES)
            sock.send(cipher_text)
            endTime = time.time()
            print("\nRuntime: %f seconds" % (endTime - startTime))
    except KeyboardInterrupt:
        sock.close()
        print("KeyboardInterrupt")
    sys.exit(0)