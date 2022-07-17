locations = [[-9, 146, "런던"], [102, 107, "수에즈"], [168, 83, "봄베이"], [241, 75, "캘커타"], [295, 62, "홍콩"], [374, 104, "요코하마"], [-293, 112, "샌 프란시스코"], [-197, 124, "뉴욕"]]

import turtle as t
import serial, time

pyserial = serial.Serial(port = "/dev/cu.usbmodem21401", baudrate = 9600)
# 초기위치 설정
t.title("필리어스 포그의 여행 시뮬레이터")
t.pen()
t.hideturtle()
t.bgpic("bg.png")
t.penup()
t.speed(0)
t.goto(locations[0][0], locations[0][1])
t.pendown()
t.speed(1)
global currentloca
currentloca = "런던"

def go(location):
    global currentloca
    if (currentloca == "요코하마" or currentloca == "홍콩") and (location[2] == "샌 프란시스코" or location[2] == "뉴욕"):
        t.goto(500, 104)
        t.penup()
        t.speed(0)
        t.goto(-500, 104)
        t.pendown()
        t.speed(1)
        t.goto(location[0], location[1])
    else:
        t.goto(location[0], location[1])
    t.color("red")
    t.dot(5)
    t.color("black")
    currentloca = location[2]

i = 0
while True:
    time.sleep(0.1)
    if pyserial.readable():
        go(locations[int(pyserial.readline())])
    if i == 8: break

t.done()
