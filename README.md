# Bai1_GPIO : chương trình đảo trạng thái đầu ra của Led trên Board STM32F4 khi nútấn trên Board được nhấn.
</br>
<h2>Bước 1: Tải thư viện SDK_1.0.3_NUCLEO-F401RE và lưu trữ ở thư mục dễ
tìm </h2>
</br>
<h2>
 Bước 2: Tạo project bằng phần mềm STM32CubeIDE</h2>
 </br>
 <h2>
 Bước 3: Thêm thư viện SDK_1.0.3_NUCLEO-F401RE vào project vừa tạo theo chỉ dẫn sau:</h2>
 </br>
+ Trỏ chuột vào project và ấn chuột phải.
</br>
+ Chọn Properties → C/C++ Genaral → Path and Symbols → Source
</br>
Location → Link Folder → chọn tích Link to folder in the system → chọn Browse để chọn đến file SDK_1.0.3_NUCLEO-F401RE và nhấn OK.
</br>
<h2>Bước 4: Sau khi đã thêm thư viện SDK_1.0.3_NUCLEO-F401RE, các bạn cần phải tạo đường dẫn đến thư mục.</h2>
</br>
+ Trỏ chuột vào project và ấn chuột phải.
</br>
+ Chọn Properties → C/C++ Build → Setting → Tool Setting → Include
</br>
paths trong MCU GCC Compiler → chọn Add → chọn Workspace… và
chọn các đường dẫn sau:
</br>
1. SDK_1.0.3_NUCLEO-F401RE/shared/Drivers/CMSIS/Include
</br>
2. SDK_1.0.3_NUCLEO-F401RE/shared/Drivers/STM32F401RE_StdPe
riph_Driver/inc
</br>
3. SDK_1.0.3_NUCLEO-F401RE/shared/Middle/button
</br>
4. SDK_1.0.3_NUCLEO-F401RE/shared/Middle/rtos
</br>
5. SDK_1.0.3_NUCLEO-F401RE/shared/Middle/serial
</br>
6. SDK_1.0.3_NUCLEO-F401RE/shared/Middle/buzzer
</br>
7. SDK_1.0.3_NUCLEO-F401RE/shared/Middle/led
</br>
8. SDK_1.0.3_NUCLEO-F401RE/shared/Middle/sensor
</br>
9. SDK_1.0.3_NUCLEO-F401RE/shared/Middle/ucglib
</br>
10. SDK_1.0.3_NUCLEO-F401RE/shared/Utilities
</br>
Trong Properties → C/C++ Build → Setting → Tool Setting →
Libraries trong MCU GCC Linker → chọn Add… trong Libraries(-l) →
viết Libraries và Add… trong Library search paths (-L) thêm đường dẫn
sau: SDK_1.0.3_NUCLEO-F401RE\lib_stm
</br>
<h2>Bước 5: Thêm các thư viện "stm32f401re gpio.h", "stm32f401re_rcc.h" bằng câu lệnh #include.</h2>
</br>
<h2>Bước 6: Định nghĩa các macro với tên gọi dễ nhớ giúp bạn dễ dàng trong khi
bạn viết chương trình</h2>
</br></br>
![Kết quả](https://user-images.githubusercontent.com/117442476/224863377-373c01ba-6f22-4fb7-810e-0313f99106cc.png)
</br></br>
<h2>Bước 7: Cấu hình chân PA5 của led trên Board STM32 ở chế độ output.</h2></br>
● Khai báo biến thuộc kiểu dữ liệu struct GPIO.</br>
● Cấp xung clock hoạt động cho Port A.</br>
● Chọn chân sử dụng với chức năng điều khiển Led.</br>
● Chọn chân điều khiển led ở chế độ Output.</br>
● Tốc độ xử lý trên chân là 50MHz.</br>
● Chọn chế độ là đẩy kéo Push Pull.</br>
● Trạng thái ban đầu trên chân là kéo xuống GND Pull Down.</br>
● Khởi tạo tất cả các giá trị bên trên bằng cách sử dụng hàm GPIO_Init với</br>
đối số truyền vào là GPIOA và GPIO_InitStructure</br></br>

![Kết quả](https://user-images.githubusercontent.com/117442476/224864406-44f37af0-167e-4a63-ae37-5ba6ace81362.png)
</br></br></br>
 <h2>Bước 8: Cấu hình chân PC13 của nút nhấn trên Board STM32F401 ở chế độ
input.</h2></br>
● Khai báo biến thuộc kiểu dữ liệu struct GPIO.</br>
● Cấp xung clock cho Port C.</br>
● Chọn chân sử dụng làm chức năng nút ấn.</br>
● Chọn chế độ trên chân GPIO là Input.</br>
● Tốc độ xử lý là 50MHz</br>
● Trạng thái Kéo trở lên dương nguồn Pull Up.</br>
● Khởi tạo tất cả các giá trị bên trên bằng cách sử dụng hàm GPIO_Init với</br>
đối số truyền vào là GPIOC và GPIO_InitStructure.</br></br>
![Kết quả](https://user-images.githubusercontent.com/117442476/224864440-026fcb00-fd2e-4a59-8aca-d01d56380933.png)
</br></br></br>
<h2>Bước 9: Xây dựng hàm điều khiển Led với tham số truyền vào là GPIO nào và
chân được kết nối để điều khiển led.</h2></br>
● Khi muốn bật led cần ghi mức logic 1 vào bit tương ứng của thanh ghi
BSRRL.</br>
● Khi muốn tắt led cần ghi mức logic 1 vào bit tương ứng của thanh ghi
BSRRH.</br></br>
![Kết quả](https://user-images.githubusercontent.com/117442476/224864461-0c38f0da-19d1-4a29-9cea-491b40bd6c9c.png)
</br></br></br>
<h2>Bước 10: Xây dựng hàm đọc giá trị nút ấn:</h2></br>
● Muốn đọc trạng thái nút ấn cần dịch bit tương ứng với nút ấn trong thanh
ghi IDR về bit số 0.</br>
● Sau đó sử dụng phép toán tử (AND) nhân giá trị sau khi dịch với 0x01 để
đọc giá trị trên chân làm chức năng nút ấn.</br></br>

![Kết quả](https://user-images.githubusercontent.com/117442476/224864487-6c6ef3ea-d7d1-490a-a05e-f76aabde233b.png)
</br></br></br>

<h2>Bước 11: Trong hàm while(1), thực hiện thuật toán đảo trạng thái led khi được
ấn nút</h2></br></br>

![Kết quả](https://user-images.githubusercontent.com/117442476/224864529-81524456-faa2-45e0-ad65-6281d850f00f.png)
