from Cryptodome.Hash import SHA256
from Cryptodome.PublicKey import RSA
from Cryptodome.Signature import pkcs1_15
import os

def writeKeys(key, fname):
    with open(fname + '.key.pem', "wb") as pub:
        pub.write(key.publickey().export_key('PEM'))
  
def readKey(fname):
    with open(fname + '.key.pem', "rb") as pub:
        key = RSA.import_key(pub.read())
    return key

if __name__ == '__main__':
    fname = input("Введите имя файла: ")
    action = input("Введите действие sing(s)/check(c):")
    if action == 's':
        print("Создание публичного и приватного ключей...")
        key = RSA.generate(1024, os.urandom)
        writeKeys(key, fname)
        print("Ключи созданы и записаны в файл.")

        # Получаем хэш файла
        try:
            h = SHA256.new()
            with open(fname, "rb") as f:
                for chunk in iter(lambda: f.read(4096), b""):
                    h.update(chunk)
        except(FileNotFoundError):
            print("Файл не найден")
            exit(0)
                
        
        # Подписываем хэш
        signature = pkcs1_15.new(key).sign(h)

        with open(fname + '.signature', "wb") as pub:
            pub.write(signature)
        print("Электронная подпись успешно создана.")

    if action == 'c':
        try: 
            key = readKey(fname)
            pubkey = key.publickey()
            print("Ключ прочитан из файла.")

            with open(fname + '.signature', "rb") as pub:
                signature = pub.read()
            print("Считана электронная подпись.")
        except(FileNotFoundError):
            print("Файл не найден. Проверьте наличие ключа и сигнатуры")
            exit(0)
        
        try:
            # Получаем хэш файла
            h = SHA256.new()
            with open(fname, "rb") as f:
                for chunk in iter(lambda: f.read(4096), b""):
                    h.update(chunk)
        except(FileNotFoundError):
            print("Файл не найден")
            exit(0)

        try:       
            pkcs1_15.new(pubkey).verify(h, signature)
            print("Подпись подтверждена. ")
        except(ValueError):
            print("Неверная подпись!")
