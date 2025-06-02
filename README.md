# Hệ thống giám sát và điều khiển tưới nước tự động bằng NodeMCU

## Mô tả dự án

Dự án này sử dụng NodeMCU để giám sát **độ ẩm đất** và **nhiệt độ môi trường**, kết hợp với nền tảng **Blynk** để hiển thị và cảnh báo từ xa. Hệ thống điều khiển **máy bơm nước** thông qua relay dựa trên các ngưỡng được cài đặt trước. Kết quả cũng được hiển thị trực tiếp trên **màn hình OLED**.

---

## Thành phần chính

- **NodeMCU ESP8266**
- **Cảm biến độ ẩm đất** (kết nối chân A0)
- **Cảm biến nhiệt độ** (kết nối chân D0)
- **Relay module điều khiển máy bơm**
- **Màn hình OLED SSD1306**
- **LED hiển thị trạng thái (đỏ, xanh, vàng)**
- **Nền tảng Blynk để hiển thị dữ liệu và điều khiển từ xa**

---

## Chức năng

### 1. Giám sát độ ẩm đất

- **Đọc dữ liệu từ cảm biến qua chân A0**
- **Hiển thị lên Blynk (Virtual Pin V3)**
- **Cho phép người dùng cài đặt ngưỡng trên và ngưỡng dưới**

#### Hành động:

| Trạng thái độ ẩm | NodeMCU hành động | Blynk | OLED |
|------------------|-------------------|-------|------|
| Cao hơn ngưỡng trên | - Bật LED vàng<br>- Tắt máy bơm (ngắt relay) | - Bật LED vàng<br>- Gửi cảnh báo "Độ ẩm cao" | Hiển thị "Độ ẩm cao" |
| Thấp hơn ngưỡng dưới | - Bật LED đỏ<br>- Mở máy bơm (đóng relay) | - Bật LED đỏ<br>- Gửi cảnh báo "Độ ẩm thấp" | Hiển thị "Đang tưới nước" |
| Trong ngưỡng | - Bật LED xanh<br>- Tắt máy bơm (đóng relay) | - Bật LED xanh | Hiển thị "Độ ẩm bình thường" |

---

### 2. Giám sát nhiệt độ

- **Đọc dữ liệu từ cảm biến qua chân D0**
- **Hiển thị lên Blynk (Virtual Pin V1)**
- **Cho phép người dùng cài đặt ngưỡng trên và ngưỡng dưới**

#### Hành động:

| Trạng thái nhiệt độ | NodeMCU hành động | Blynk | OLED |
|---------------------|-------------------|-------|------|
| Cao hơn ngưỡng trên | - Bật LED vàng<br>- Tắt máy bơm (ngắt relay) | - Bật LED vàng<br>- Gửi cảnh báo "Nhiệt độ cao" | Hiển thị "Nhiệt độ cao" |
| Thấp hơn ngưỡng dưới | - Bật LED đỏ<br>- Mở máy bơm (đóng relay) | - Bật LED đỏ<br>- Gửi cảnh báo "Nhiệt độ thấp" | Hiển thị "Đang tưới nước" |
| Trong ngưỡng | - Bật LED xanh<br>- Tắt máy bơm (đóng relay) | - Bật LED xanh | Hiển thị "Nhiệt độ bình thường" |

---

## Giao diện Blynk

- **V1**: Nhiệt độ
- **V3**: Độ ẩm đất
- **LED Widget**: hiển thị các trạng thái tương ứng
- **Notifications**: cảnh báo khi vượt ngưỡng

---

## Hướng dẫn sử dụng

1. Nạp code lên NodeMCU bằng Arduino IDE.
2. Cấu hình kết nối WiFi và token Blynk trong code.
3. Cài đặt ngưỡng trên/dưới cho độ ẩm và nhiệt độ trong ứng dụng Blynk.
4. Quan sát dữ liệu cảm biến, trạng thái relay, và OLED.

---

## Tác giả

Dự án thực hiện bởi [Vũ Hoàng Giang], năm 2024.

---

