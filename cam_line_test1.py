import cv2
import numpy as np
import serial
import time

cap = cv2.VideoCapture(0)
ser = serial.Serial('COM3', 9600, timeout=1)

while True:
    ret, frame = cap.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    _, thresh = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)
    contours, _ = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    if len(contours) > 0:
        c = max(contours, key=cv2.contourArea)
        M = cv2.moments(c)

        if M['m00'] != 0:
            cx = int(M['m10'] / M['m00'])
            cy = int(M['m01'] / M['m00'])

            if cx < 320:
                # Turn left
                error = 320 - cx
                speed = int(abs(error) / 3)
                ser.write(bytes([0x01, 0x00, speed]))
            else:
                # Turn right
                error = cx - 320
                speed = int(abs(error) / 3)
                ser.write(bytes([0x02, 0x00, speed]))
        else:
            # Line lost, stop
            ser.write(bytes([0x00, 0x00, 0x00]))

    cv2.drawContours(frame, contours, -1, (0, 255, 0), 3)
    cv2.imshow('frame', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

ser.close()
cap.release()
cv2.destroyAllWindows()