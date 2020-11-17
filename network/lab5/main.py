import smtplib
import sys
import os
from os.path import isfile, basename, splitext
import time
from email.mime.application import MIMEApplication
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email.utils import COMMASPACE, formatdate
from email import encoders
from email.mime.text import MIMEText


if __name__ == "__main__":
    print("Please input strings in '  ' ")
    to_email = input("Enter to: ")
    from_email = input("Enter from: ")
    password = input("Enter password: ")
    title = input("Enter title: ")
    body = input("Enter body: ")
    filename = input("Enter filename: ")
    interval = input("Enter interval: ")

    print(to_email)
    print(from_email)
    print(password)
    print(title)
    print(body)
    print(filename)


    mime = MIMEMultipart()
    mime['From'] = from_email
    mime['To'] = to_email
    mime['Date'] = formatdate(localtime=True)
    mime['Subject'] = title
    mime.attach(MIMEText(body, 'plain'))
    try:
        with open(filename, 'rb') as file:
            part = MIMEApplication(file.read(), Name=basename(filename))
        part.add_header('Content-Disposition', 'attachment; filename="{}"'.format(filename))
        mime.attach(part)
    except Exception:
        pass
   
    while True: 
        try:
            server_ssl = smtplib.SMTP_SSL('smtp.gmail.com', 465)
            server_ssl.ehlo()
            server_ssl.login(from_email, password)
            server_ssl.sendmail(mime['From'], mime['To'], mime.as_string())
            server_ssl.close()
        

            print('Email sent!')
        except Exception:
            print("Samething went wrong!")
        time.sleep(interval)

