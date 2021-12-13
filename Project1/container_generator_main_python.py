## Main
f = open("Output.txt", "a")

Rect = Rectangle()
Rect_list = list()

range_x1 = range_y1 = range_x2 = range_y2 = 0

for i in range(Rect_num):
    rect_xy = Rect.gen_xyPairs(range_x1, range_y1, range_x2, range_y2)

    range_x1 = rect_xy[0]
    range_y1 = rect_xy[1]
    range_x2 = rect_xy[2]
    range_y2 = rect_xy[3]

    print("rect_xy = ", rect_xy)
    print("Rect number = %d" %i)
    Rect_list.append(rect_xy)

# print Rect_list

start_time = time.time()
#print start_time

ret = rectangleArea(Rect_list)

end_time = time.time()
#print end_time

execution_time_microSecond = (end_time - start_time) * 1000000
print "total area = %d" % ret
print "execution time = %d us" % execution_time_microSecond
print "execution time = %d s" % (end_time - start_time)

rect_num_string = "Rectangle number: " + str(Rect_num) + "\n"
f.write(rect_num_string)
elasped_time_string = "Elasped time: " + str(end_time - start_time) + "\n"
f.write(elasped_time_string)
total_area_string = "Total area: " + str(ret) + "\n\n\n"
f.write(total_area_string)

f.close()
