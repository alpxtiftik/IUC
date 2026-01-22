//1306220054 Ahmet Alp Tiftik - Veri Yapıları Ödevi. 




#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

struct Capital {
    std::string name; // Başkent adı.
    double latitude;  // Enlem.
    double longitude; // Boylam.
    double x;         // Mercator projeksiyonu'ndaki x değeri.
    double y;         // Mercator projeksiyonu'ndaki y değeri.
    double distanceToCenter; // Merkeze olan mesafe. 
};

/* 
Alttaki fonksiyon verilen coğrafi koordinat sistemi (enlem ve boylam) formatından
Mercator projeksiyonu (x, y) şekline dönüştürür. 
Dönüşüm, küresel yüzeydeki noktaları düzlemsel bir harita üzerinde gösterilebilir hale getirir.
*/
std::pair<double, double> transformCoordinates(double lat, double lon) {
    const double R = 6378137.0; // Dünyanın yarıçapı (metre).

   
    if (lat < -90 || lat > 90 || lon < -180 || lon > 180) { // Enlem ve boylam sınırlarının geçerliliği kontrol edilir
        throw std::runtime_error("Geçersiz enlem veya boylam değeri.");
    }

    // Dönüşüm için gerekli x ve y hesaplamaları
    double x = R * lon * M_PI / 180.0; // Boylam değerinden x koordinatını hesaplar
    double y = R * std::log(std::tan(M_PI / 4.0 + lat * M_PI / 360.0)); // Enlem değerinden y koordinatını hesaplar

    return {x, y};
}

std::vector<Capital> readCSV(const std::string& filename) {// CSV dosyasını okuyarak başkentleri bir vector içine yükleyen fonksiyon. 
    std::vector<Capital> capitals; // Başkentlerin tutulacağı vektör.
    std::ifstream file(filename);
    std::string line;


    if (!file.is_open()) {//Dosya açılmazsa hata döndürür. 
        throw std::runtime_error("Gereken dosya 'baskentler_temiz.csv' bulunamadı.");
    }
    
    std::getline(file, line); // Dosya başlığını atlar. 

    // Her bir satırı okuma işlemi
    while (std::getline(file, line)) {
        std::stringstream ss(line); // Satır için stringstream oluşturur. 
        Capital capital; // Yeni bir başkent nesnesi oluşturur.

        std::getline(ss, capital.name, ','); // Başkentin adı okur
        ss >> capital.latitude; // Enlem değeri okur.
        ss.ignore(); // Virgül atlar. 
        ss >> capital.longitude; // Boylam değeri okur.

        // Geçersiz veri varsa atlar.
        if (ss.fail()) continue;

        // Aynı başkent zaten vektörde varsa eklemez.
        bool isDuplicate = std::any_of(capitals.begin(), capitals.end(),
            [&capital](const Capital& existingCapital) {
                return (existingCapital.name == capital.name || 
                        (existingCapital.latitude == capital.latitude && 
                         existingCapital.longitude == capital.longitude));
            });

        if (isDuplicate) 
            continue;

        // Coğrafi Koordinat'tan Mercator'a dönüşüm yapar. 
        auto [x, y] = transformCoordinates(capital.latitude, capital.longitude);
        capital.x = x;
        capital.y = y;

        // Başkent'i listeye ekler.
        capitals.push_back(capital);
    }

    return capitals; // Başkentlerin listesi döndürür.
}

// Başkentlerin merkeze olan uzaklıklarını hesaplar.
void calculateDistances(std::vector<Capital>& capitals) {    
    for (auto& capital : capitals) {
        // Her başkent için merkeze uzaklığını hesaplar (x ve y'nin 0'a uzaklığı).
        capital.distanceToCenter = std::sqrt(std::pow(capital.x - 0, 2) + std::pow(capital.y - 0, 2));
    }
}

std::vector<std::vector<std::string>> groupCapitalsIntoCircles(const std::vector<Capital>& capitals) {
    std::vector<Capital> sortedCapitals = capitals;

    // Başkentleri merkeze uzaklığa göre sıralar.
    std::sort(sortedCapitals.begin(), sortedCapitals.end(), [](const Capital& a, const Capital& b) {
        return a.distanceToCenter < b.distanceToCenter;
    });

    std::vector<std::vector<std::string>> circles;

    // Her bir çember için 3 başkent ekler.
    for (size_t i = 0; i < sortedCapitals.size(); i += 3) {
        std::vector<std::string> circle;
        for (size_t j = i; j < i + 3 && j < sortedCapitals.size(); ++j) {
            circle.push_back(sortedCapitals[j].name);
        }
        circles.push_back(circle);
    }

    // Son çemberin eleman sayısı 3'ten az ise bir önceki çembere ekler.
    if (circles.size() > 1 && circles.back().size() < 3) {
        circles[circles.size() - 2].insert(
            circles[circles.size() - 2].end(),
            circles.back().begin(),
            circles.back().end()
        );
        circles.pop_back();
    }

    return circles;
}

int main() {
    try {
        std::string filename = "baskentler_temiz.csv"; // CSV dosyasının adı
        auto capitals = readCSV(filename); // Dosyadan başkentler okur.

        calculateDistances(capitals); // Başkentlerin uzaklıklarını hesaplar.

        // Çemberlere ayır ve yazdır
        auto circles = groupCapitalsIntoCircles(capitals);
        std::cout << "Toplam: " << circles.size() << " çember.\n";
        for (size_t i = 0; i < circles.size(); ++i) {
            std::cout << i + 1 << ". ";
            for (const auto& name : circles[i]) {
                std::cout << name << (name == circles[i].back() ? "\n" : ", ");
            }
        }
    } catch (const std::exception& e) {
        // Hata mesajı yazdırır.
        std::cerr << "Hata: " << e.what() << std::endl;
    }

    return 0;
}
