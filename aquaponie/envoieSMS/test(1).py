import mysql.connector
import RPi.GPIO as GPIO
import time
import re
from sim800l import SIM800L
sim800l=SIM800L('/dev/ttySC0')

GPIO.setmode(GPIO.BCM)

GPIO.setup(23, GPIO.OUT, initial=GPIO.HIGH)


try:
    connection = mysql.connector.connect(host='localhost',
                                     database='aquaponie',
                                     user='admin',
                                     password='1234')
    select = """SELECT TELEPHONE FROM utilisateur"""

    cursor = connection.cursor()
    cursor.execute(select)
        
    row10 = cursor.fetchall();
    for i in range(len(row10)):
        var1 = row10[i]
        var1 = re.sub('[u(),\']', '', str(var1))
        print("Telephone = ", "+33682203986")
        print("Telephone = ", var1)
    
        select = """SELECT * FROM seuil"""
        
        cursor = connection.cursor()
        cursor.execute(select)
        
        record = cursor.fetchall();
        
        print("Affichage chaque colonne")
        
        for row in record:
            print("OXYGENE MAX = ", row[1])
            print("TEMPERATURE_MAX = ", row[2])
            print("PH_MAX = ", row[3])
            print("CONDUCTIVITE_MAX = ", row[4])
            print("OXYGENE_MIN = ", row[5])
            print("TEMPERATURE_MIN = ", row[6])
            print("PH_MIN = ", row[7])
            print("CONDUCTIVITE_MIN = ", row[8])
            omax = row[1]
            tmax = row[2]
            pmax = row[3]
            cmax = row[4]
            omin = row[5]
            tmin = row[6]
            pmin = row[7]
            cmin = row[8]
            
        select2 = """SELECT TEMPERATURE FROM temperature ORDER BY DATE DESC"""
            
        cursor = connection.cursor()
        cursor.execute(select2)

        record = cursor.fetchall();
            
        for row1 in record:
            print("TEMPERATURE= ", row1[0])

            temperature = row1[0]

        if temperature < tmin:
            sim800l.setup()

            sms="Temperature trop faible"
            sim800l.send_sms(var1,sms)
        
        if temperature > tmax:
            sim800l.setup()

            sms="Temperature trop haute"
            sim800l.send_sms(var1,sms)
        
            
        select3 = """SELECT OXYGENE FROM oxygene ORDER BY DATE DESC"""
            
        cursor = connection.cursor()
        cursor.execute(select3)

        record = cursor.fetchall();
            
        for row2 in record:
            print("OXYGENE= ", row2[0])

            oxygene = row2[0]

        if oxygene < omin:
            sim800l.setup()

            sms="Oxygene trop faible"
            sim800l.send_sms(var1,sms)
        
        if oxygene > omax:
            sim800l.setup()

            sms="Oxygene Trop haute"
            sim800l.send_sms(var1,sms)
            
        select4 = """SELECT PH FROM ph ORDER BY DATE DESC"""
            
        cursor = connection.cursor()
        cursor.execute(select4)

        record = cursor.fetchall();
            
        for row3 in record:
            print("PH= ", row3[0])

            PH = row3[0]

        if PH < pmin:
            sim800l.setup()

            sms="PH trop faible"
            sim800l.send_sms(var1,sms)
        
        if PH > pmax:
            sim800l.setup()

            sms="PH Trop haut"
            sim800l.send_sms(var1,sms)
            
        select5 = """SELECT CONDUCTIVITE FROM conductivite ORDER BY DATE DESC"""
            
        cursor = connection.cursor()
        cursor.execute(select5)

        record = cursor.fetchall();
            
        for row4 in record:
            print("conductivite= ", row4[0])

            conductivite = row4[0]

        if conductivite < cmin:
            sim800l.setup()

            sms="Conductivite trop faible"
            sim800l.send_sms(var1,sms)
        
        if conductivite > cmax:
            sim800l.setup()

            sms="Conductivite Trop haute"
            sim800l.send_sms(var1,sms)
          
except mysql.connector.Error as e:
    print("Erreur")
        
finally:
    if connection.is_connected():
        connection.close()
        cursor.close()
        print("Connexion ferme premiere")
    

    

