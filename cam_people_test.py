import cv2
import numpy as np
import serial


# 시리얼 통신을 위한 아두이노와의 연결
ser = serial.Serial('COM3', 9600) # 포트와 보레이트는 해당 아두이노에 맞게 설정

# YOLOv5 모델 로드
net = cv2.dnn.readNet("yolov5-master/yolov5s.pt")
layer_names = net.getLayerNames()
output_layers = [layer_names[i[0] - 1] for i in net.getUnconnectedOutLayers()]

# 웹캠 열기
cap = cv2.VideoCapture(0)

while True:
    # 웹캠에서 프레임 읽어오기
    ret, frame = cap.read()

    # 프레임을 YOLOv5 모델에 입력하기 위한 전처리
    blob = cv2.dnn.blobFromImage(frame, 0.00392, (416, 416), (0, 0, 0), True, crop=False)
    net.setInput(blob)
    outs = net.forward(output_layers)

    # 인식된 사람의 위치 파악하여 아두이노로 제어값 전송
    for out in outs:
        for detection in out:
            scores = detection[5:]
            class_id = np.argmax(scores)
            confidence = scores[class_id]
            if confidence > 0.5 and class_id == 0:  # 사람 클래스에 대한 confidence가 0.5 이상인 경우
                center_x = int(detection[0] * frame.shape[1])
                center_y = int(detection[1] * frame.shape[0])
                # 아두이노로 좌우 이동값 전송
                if center_x < frame.shape[1] // 3:
                    ser.write(b'left\n')
                elif center_x > frame.shape[1] * 2 // 3:
                    ser.write(b'right\n')
                else:
                    ser.write(b'stop\n')

    cv2.imshow('YOLOv5 Object Detection', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# 리소스 해제
cap.release()
cv2.destroyAllWindows()
