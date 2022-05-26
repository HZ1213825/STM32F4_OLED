
import cv2 as cv
import numpy as np
sl=50#数量
h=64#行数
l=128#列数
yz=140#阈值

sl=sl+1
def threshold_image(image,a):
    gray = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
    #cv.imshow('origin', gray)

    ret, binary = cv.threshold(gray, yz, 255, cv.THRESH_BINARY)# 自定义阈值为150,大于150的是白色 小于的是黑色
    #cv.imwrite("./1/"+str(a)+".bmp",binary)#输出
    # cv.imshow('origin',binary)#调试用
    # cv.waitKey(0)
    return binary

for a in range(1,sl):
    src = cv.imread(r"C:\Users\HZ12138\Desktop\1\ ("+str(a)+").jpg")
    zj=threshold_image(src,str(a))
    tst=np.asarray(zj)
    np.set_printoptions(threshold=np.inf)
    js=0
    txt="\nconst uint8_t t"+str(a)+"[128][8]=\n{"
    # 取反用
    # for i in range(h):
    #     for j in range(l):
    #         if tst[i][j] == 255:
    #             tst[i][j]=0
    #         elif tst[i][j]==0:
    #             tst[i][j]=1

    # 不取反用
    for i in range(h):
        for j in range(l):
            if tst[i][j] == 255:
                tst[i][j]=1
            elif tst[i][j]==0:
                tst[i][j]=0
    t=0
    for i in range(0,h,8):
        for j in range(l):
            js=0
            for z in range(0,8):
                js=js*2+tst[i+7-z][j]
            txt+=str(hex(js))+","
            t+=1
            if t==16:
                txt+="\n"
                t=0
    txt=txt.rstrip(",")
    txt+="};"
    #print(tst)
    with open("1.txt","a") as fp:
        fp.write(txt)
    print("t"+str(a)+',',end="")