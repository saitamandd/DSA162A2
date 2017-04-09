# Bài tập lớn 02
## 1. Mô tả
Trong bài tập lớn này, chúng ta cũng xem xét dữ liệu như bài tập lớn trước.
Mục đích chính của Bài tập này là tìm cách thống kê các phương tiện và số lần đã di chuyển qua một vị trí quan sát đặc thù được xác định trước.

Việc xác định một phương tiện di chuyển qua một vị trí địa lý cho trước không hề dễ dàng bởi nhiều lý do:
- Không thể lưu trữ một cách liên tục hành trình của các phương tiện vận tải
- Hệ thống vật lý xác định tọa độ địa lý luôn có sai số và sai số khác nhau trên mỗi phương tiện.

Do đó, hệ thống đề xuất một chiến lược xấp xỉ để xác định xem một vị trí trong hành trình của một phương tiện được 
lưu trữ có __ở gần__ vị trí quan sát.
Khái niệm `ở gần` được hiện thực bởi ngưỡng sai số chấp nhận: 
`Delta_lat`, `Delta_long`.

Ngoài ra, do vị trí được lưu trữ bởi hai thông tin: 
kinh độ (longitude) và vĩ độ (latitude). Để tính toán nhanh, 
bài này đề xuất một giải pháp là sử dụng hai cây AVL: 
một cây dùng để lưu trữ danh sách các phương tiện theo kinh độ 
và cây còn lại dùng lưu trữ theo vĩ độ.

Một phương tiện vận tải được xem là có hành trình đi qua vị trí 
quan sát nếu tồn tại một vị trí `X` trong hành trình của phương 
tiện này có __ở gần__ vị trí `Y` quan sát, nghĩa là

    Y_lat  - Delta_lat  <= X_lat  <= Y_lat  + Delta_lat
    Y_long - Delta_long <= X_long <= Y_long + Delta_long

Trong bài tập lớn này, chúng ta sẽ phát triển một module cơ bản để thống kê mật độ giao thông tại một vị trí thông qua hệ thống lưu trữ các 
thông tin GPS lưu trữ được từ hành trình các phương tiện vận tải.

## 2. Yêu cầu
Trong bài tập lớn này, sinh viên sẽ được cung cấp hai file trong đó
- Một file chứa dữ liệu nhập, bao gồm các mẫu thông tin về trạng thái của phương tiện vận tải tại một thời điểm. Các mẫu dữ liệu nhập này đều được lưu trữ và biểu diễn dưới dạng danh sách liên kết (linked list).
- Một file chứa một (hoặc một tập các) yêu cầu truy xuất. Chi tiết cụ thể yêu cầu công việc sinh viên phải làm sẽ mô tả trong phần 4.

## 3. Dữ liệu
### 3.1. Dữ liệu nhập
Dữ liệu nhập của chương trình được chứa trong file input như sau:

| # | Nội dung |
|---|:---------|
|1| 1B03755,1,0000001234567890,0.0,1.472989878E9,106.781668333333,10.65749,0.0,348.0,0,1,0,0,0,1,0.0,0.0 |
|2| 61C21884,1,,0.0,1.472989881E9,106.411811666667,11.1932933333333,0.0,288.0,0,0,0,0,0,0,0.0,0.0 |
|3| 51B14725,1,0000001234567891,0.0,1.472989881E9,106.689196666667,10.7733133333333,0.0,30.0,1,1,0,0,0,0,0.0,0.0 |
|4| 51C65728,1,0000,0.0,1.472989881E9,106.6605,10.8074,0.0,0.0,0,0,0,0,0,0,0.0,0.0 |

Mỗi dòng trong file sẽ chứa một loạt các thông tin mô tả như sau:
- Phần tử đầu tiên: biển số xe (vehicle ID).
- Phần tử thứ 5: thời điểm xe gửi tín hiệu GPS (timestamp).
- Phần tử thứ 6: kinh độ (longitude).
- Phần tử thứ 7: vĩ độ (latitude).

Ngoài ra, xe được xem là đang dừng khi toạ độ tại thời điểm hiện tại so với 
thời điểm trước đó cách nhau dưới 5m.

### 3.2. Dữ liệu xuất
Dữ liệu sinh viên xuất ra cần tuân thủ các quy tắc sau:
 + Số nguyên: không cần định dạng
 + Số thực: độ chính xác __*12*__ chữ số
 + Các dòng dữ liệu: với mỗi request, sinh viên xuất ra
 thông tin trên cùng một dòng, cách nhau bởi khoảng trắng.
 + Nếu dữ liệu gồm nhiều dòng thì mỗi dòng xuất thông tin của một đối tượng
 (vd: dữ liệu của cùng một bus). 
 + Nếu request là dạng command, sinh viên xuất 
 ra `nội dung request`: `Succeed`/`Failed`.

## 4. Các yêu cầu truy xuất
Các yêu cầu có thể được xử lý trên database.

| Mã sự kiện | Ý nghĩa |
| ---------- | ------- |
| 1AXXYXXXXX Y_lat Delta_lat   | xác định xem phương tiện vận tải mang biển số `XXYXXXXX` có hành trình đi qua vị trí `Y` hay không (trên trục latitude) |
| 1BXXYXXXXX Y_long Delta_long | xác định xem phương tiện vận tải mang biển số `XXYXXXXX` có hành trình đi qua vị trí `Y` hay không (trên trục longitude)|
| 2AXXYXXXXX Y_lat Delta_lat   | xác định số lượng điểm lưu trữ trong hành trình phương tiện vận tải mang biển số `XXYXXXXX` có ở gần vị trí `Y` (trên trục latitude)|
| 2BXXYXXXXX Y_long Delta_long | xác định số lượng điểm lưu trữ trong hành trình phương tiện vận tải mang biển số `XXYXXXXX` có ở gần vị trí `Y` (trên trục longitude)|
| 3XXYXXXXX  Y_lat Y_long Delta_lat Delta_long | xác định số lần phương tiện vận tải mang biển số `XXYXXXXX` có đi qua vị trí `Y`|
| 4 Y_lat Y_long Delta_lat Delta_long | xác định số lượng phương tiện vận tải có hành trình đi qua vị trí `Y`|
| 5 Y_lat Y_long Delta_lat Delta_long | xác định số lượng điểm lưu trữ ở gần vị trí `Y`|
| 6XXYXXXXX Y_lat Y_long Delta_lat Delta_long | xác định xem phương tiện vận tải mang biển số `XXYXXXXX` có hành trình đi qua vị trí `Y` hay không|
| 7XXYXXXXX Y_lat Y_long Delta_lat Delta_long | xác định số lượng điểm lưu trữ trong hành trình phương tiện vận tải mang biển số `XXYXXXXX` có ở gần vị trí `Y`|

**Lưu ý: nếu có nhiều kết quả có thể trả về thì chọn kết quả đầu tiên theo thứ tự lưu 
trong dữ liệu đầu vào.**


## 5. Hiện thực
**Sinh viên được cung cấp các file sau:**
- `main.cpp`: mã nguồn chính của chương trình
- `dsaLib.h`: thư viện các cấu trúc dữ liệu cần dùng
- `dbLib.h`: file header chứa prototype cần thiết để quản lý database
- `dbLib.cpp`: mã nguồn hiện thực các chức năng quản lý database
- `eventLib.h`: file header chứa các prototype cần thiết để quản lý các sự kiện
- `eventLib.cpp`: mã nguồn hiện thực các hàm xử lý sự kiện

__Sinh viên được cho các hàm sau:__
- `distanceEarth`: tính khoảng cách giữa 2 điểm trên mặt đất với 
 toạ độ (latitude, longitude) cho trước.
- `loadBusDB`: đọc file và lấy dữ liệu bus vào danh sách
- `parseBusInfo`: đọc thông tin bus từ dòng dữ liệu
- `strPrintTime`: in thời gian ra một chuỗi theo định dạng yêu cầu

Đối với file thư viện `dsaLib.h`, sinh viên được cung cấp sẵn định 
nghĩa cơ bản. Ngoài ra, _để build được chương trình hoàn chỉnh, sinh viên
cần hoàn thiện các hàm còn lại trong danh sách_.

`processData.cpp`: Sinh viên hiện thực việc xử lý các yêu cầu thông qua hàm `processEvent`.
Không được thay đổi prototype của hàm này.

Sinh viên được phép tuỳ biến, chỉnh sửa `dsaLib.h` và `processData.cpp`.

**Sinh viên không được sử dụng các thư viện nào khác ngoài các thư viện đã được 
dùng trong code mẫu.**
### Build
Sinh viên thực hiện build bằng lệnh `make` từ command line trên Linux
và chạy file `dsa162a2`. Cú pháp trên linux như sau:
> `./dsa162a2 event.txt input1.txt`

trong đó `event.txt` là file chứa danh sách các sự kiện, cách nhau bởi 
  khoảng trắng hoặc ký tự xuống dòng.
  `input1.txt` là file dữ liệu xe bus, sinh viên có thể thử nghiệm với 
  các file dữ liệu khác nhau. 

Đối với các bạn dùng VisualStudio trên Windows, các bạn có thể tạo một 
project và thêm các file mã nguồn vào. Nếu không bạn có thể sử dụng hệ 
thống CMake để tự sinh project VS cho mình.
 
