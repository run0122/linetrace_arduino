import cv2
import numpy as np
import torch
import serial

ser = serial.Serial('COM3', 9600)

model = torch.hub.load('ultralytics/yolov5', 'yolov5s', pretrained=True)

cap = cv2.VideoCapture(0)  # 0번 카메라 연결
while True:
    ret, frame = cap.read()  # 프레임 읽기
    if not ret:
        break
    results = model(frame)  # 객체 감지 수행

    for detection in results.xyxy[0]:
        # 객체의 위치와 클래스 정보를 가져옵니다.
        x1, y1, x2, y2, conf, cls = detection
        label = model.names[int(cls)]

        # person 객체일 때만 그리기
        if label == 'person':
            # 객체의 위치에 사각형을 그려줍니다.
            cv2.rectangle(frame, (int(x1), int(y1)), (int(x2), int(y2)), (0, 255, 0), 2)
            # 객체의 클래스 이름과 정확도를 화면에 출력합니다.
            cv2.putText(frame, f'{label} {conf:.2f}', (int(x1), int(y1 - 10)), cv2.FONT_HERSHEY_SIMPLEX, 0.9,
                        (0, 255, 0), 2)

            # 객체의 중심점(cx, cy) 계산
            cx = int((x1 + x2) / 2)
            cy = int((y1 + y2) / 2)

            cv2.circle(frame, (cx, cy), 5, (0, 0, 255), -1)

            if cx < 210:
                ser.write(b'R')
            elif cy > 450:
                ser.write(b'L')
            else:
                ser.write(b'B')

            cv2.circle(frame, (cx, cy), 5, (255, 0, 0), -1)

            print("Average Center point: ({}, {})".format(cx, cy))

    cv2.imshow('YOLOv5', frame)  # 화면에 프레임을 출력합니다.

    height, width, channels = frame.shape

    # 하단부 중앙 1/2 영역 추출하기
    crop_width = int(width * 2 / 3)  # 가로 크기를 2배로 늘림
    crop_height = int(height / 2)
    start_x = 0
    start_y = int(height / 2)
    end_x = width
    end_y = height

    # 이미지 경계를 벗어나는 값을 사용하지 않도록 주의해야 합니다.
    if end_x > width:
        end_x = width

    cropped_frame = frame[start_y:end_y, start_x:end_x]

    # 그레이스케일 이미지로 변환하기
    gray = cv2.cvtColor(cropped_frame, cv2.COLOR_BGR2GRAY)

    # 이미지 이진화하기
    _, thresh = cv2.threshold(gray, 80, 255, cv2.THRESH_BINARY_INV)

    # 컨투어 찾기
    # contours, _ = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    # 컨투어 중 가장 큰 영역 찾기

    max_area = 0
    min_contour_area = 10000
    max_contour = None
    for contour in contours:
        area = cv2.contourArea(contour)
        if area > max_area and area > min_contour_area:
            max_area = area
            max_contour = contour

    # 가장 큰 영역의 중심점 찾기
    if max_contour is not None:
        M = cv2.moments(max_contour)
        if M["m00"] != 0:
            cx = int(M["m10"] / M["m00"])
            cy = int(M["m01"] / M["m00"])

            # 중심점 그리기
            cv2.circle(thresh, (cx, cy), 5, (0, 0, 255), -1)

            # 중심점 정보 시리얼 통신으로 전송하기
            if cx < 210:
                ser.write(b'L')
            elif cx > 450:
                ser.write(b'R')

            else:
                ser.write(b'F')

            # print("Center point: ({}, {})".format(cx, cy))

    # 프레임 보여주기
    cv2.imshow("Line Tracer", thresh)

    # 'q' 키를 눌러 종료합니다.
    if cv2.waitKey(1) == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
