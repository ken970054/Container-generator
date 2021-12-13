import random
import time

max_range = 2000000000
max_range_per_rect = 10
Rect_num = 900000

class Rectangle:

    def __init__(self):
        self.x1 = None
        self.y1 = None
        self.x2 = None
        self.y2 = None

    def gen_xyPairs(self, range_x1, range_y1, range_x2, range_y2):
        # initial Rectangle xy pair
        if range_x1 == 0 and range_y1 == 0 and range_x2 == 0 and range_y2 == 0:
            self.x1 = random.randrange(max_range_per_rect)
            self.y1 = random.randrange(max_range_per_rect)
            self.x2 = random.randrange(max_range_per_rect)
            self.y2 = random.randrange(max_range_per_rect)

            # make sure x1 != x2 and y1 != y2
            while self.x1 == self.x2 or self.y1 == self.y2:
                if self.x1 == self.x2:
                    self.x1 = random.randrange(max_range_per_rect)
                if self.y1 == self.y2:
                    self.y1 = random.randrange(max_range_per_rect)
						# adjust x, y position
            if self.x1 > self.x2:
                temp = self.x1
                self.x1 = self.x2
                self.x2 = temp
            if self.y1 > self.y2:
                temp = self.y1
                self.y1 = self.y2
                self.y2 = temp
        else:
            while True:
                ## set nextRect.x2 from range preRect.x1 to (preRect.x2 + max_range_per_rect)
                self.x2 = random.randrange(max_range_per_rect + range_x2 - range_x1 + 1) + range_x1
                ## set nextRect.x1
                if self.x2 >= range_x2:
                    self.x1 = range_x2 - random.randrange(max_range_per_rect - self.x2 + range_x2 + 1)
                else:
                    self.x1 = self.x2 - random.randrange(max_range_per_rect + 1)

                if self.x1 != self.x2:
                    break

						while True:
                ## set nextRect.y2 from range preRect.y1 to (preRect.y2 + max_range_per_rect)
                self.y2 = random.randrange(max_range_per_rect + range_y2 - range_y1 + 1) + range_y1
                ## set nextRect.y1
                if self.y2 >= range_y2:
                    self.y1 = range_y2 - random.randrange(max_range_per_rect - self.y2 + range_y2 + 1)
                else:
                    self.y1 = self.y2 - random.randrange(max_range_per_rect + 1)

                if self.y1 != self.y2:
                    break


        rect_xy = [self.x1, self.y1, self.x2, self.y2]
        return  rect_xy

def rectangleArea(RectList):
    xv = list()
    for i in range(len(RectList)):
        xv.append(RectList[i][0])
        xv.append(RectList[i][2])

    xv = sorted(set(xv))
    index = dict()

    for i in range(len(xv)):
        index[xv[i]] = i

    count = []
    for i in range(len(xv)):
        count.append(0)

    x = []
    for i in range(len(RectList)):
        x1 = RectList[i][0]
        y1 = RectList[i][1]
        x2 = RectList[i][2]
        y2 = RectList[i][3]
        x.append([y1, x1, x2, 1])
        x.append([y2, x1, x2, -1])

    x.sort()
    #print x

    ret = 0
    x_sum = 0
    currentY = 0

		for i in range(len(x)):
        y = x[i][0]
        x1 = x[i][1]
        x2 = x[i][2]
        sig = x[i][3]
        ret = ret + (y - currentY) * x_sum
        print("ret = %d") % ret
        currentY = y
        for i in range(index[x1], index[x2]):
            count[i] = count[i] + sig
        x_sum = 0
        for i in range(len(count)):
            if count[i] > 0:
                x_sum = x_sum + (xv[i + 1] - xv[i])

    return ret
