import cv2
import serial

# 시리얼 포트 설정
ser = serial.Serial('COM3', 9600)

# HOG 객체 생성
hog = cv2.HOGDescriptor()
hog.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())

cap = cv2.VideoCapture(0)

while True:
    # 프레임 읽어들이기
    ret, frame = cap.read()

    # HOG 기반의 사람 검출 수행
    (rects, weights) = hog.detectMultiScale(frame, winStride=(4, 4))

    # 검출된 사람의 중심점 계산 및 제어
    if len(rects) > 0:
        max_area = 0
        max_rect = None
        for rect in rects:
            area = rect[2] * rect[3]
            if area > max_area:
                max_area = area
                max_rect = rect

        if max_rect is not None:
            # 검출된 인간에 대한 바운딩 박스 그리기
            cv2.rectangle(frame, (max_rect[0], max_rect[1]), (max_rect[0] + max_rect[2], max_rect[1] + max_rect[3]), (0, 255, 0), 2)

            cx = max_rect[0] + int(max_rect[2] / 2)
            cy = max_rect[1] + int(max_rect[3] / 2)

            # 중심점 그리기
            cv2.circle(frame, (cx, cy), 5, (0, 0, 255), -1)

            # 중심점 정보 시리얼 통신으로 전송하기
            if cx < 200:
                ser.write(b'L')
            elif cx > 400:
                ser.write(b'R')
            else:
                ser.write(b'F')

    # 선 검출 수행
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    _, thresholded = cv2.threshold(gray, 100, 255, cv2.THRESH_BINARY)
    contours, _ = cv2.findContours(thresholded, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # 검출된 선의 중심점 계산 및 제어
    if len(contours) > 0:
        max_area = 0
        max_contour = None
        for contour in contours:
            area = cv2.contourArea(contour)
            if area > max_area:
                max_area = area
                max_contour = contour

        if max_contour is not None:
            # 검출된 선에 대한 바운딩 박스 그리기
            x, y, w, h = cv2.boundingRect(max_contour)
            cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)

            cx = x + int(w / 2)
            cy = y + int(h / 2)

            # 중심점 그리기
            cv2.circle(frame, (cx, cy), 5, (0, 255, 0), -1)

            # 중심점 정보 시리얼 통신으로 전송하기
            if cx< 200:
                ser.write(b'L')
            elif cx > 400:
                ser.write(b'R')
            else:
                ser.write(b'F')
# 화면에 프레임 표시
    cv2.imshow("Frame", frame)

# 'q' 키를 누르면 종료
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()
ser.close()