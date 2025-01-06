#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // for rand()
#include <ctime>   // for srand()
#include <algorithm> // for std::sort

using namespace std;

// kacSinifKullanilacak fonksiyonu
int kacSinifKullanilacak(int ogrSayi, const vector<int>& sinifKapasite) {
    int kapasitelerToplami = 0;
    int kullanilacakSinifSayisi = 0;
    for (size_t i = 0; i < sinifKapasite.size(); i++) {
        kapasitelerToplami += sinifKapasite[i];
        kullanilacakSinifSayisi++;
        if (kapasitelerToplami >= ogrSayi)
            break;
    }
    return kullanilacakSinifSayisi;
}

// dagilimBul fonksiyonu
void dagilimBul(const vector<int>& sinifKapasite, int ogrSayi, vector<int>& sinifMevcut) {
    int kapasitelerToplami = 0;
    int a = kacSinifKullanilacak(ogrSayi, sinifKapasite);
    vector<float> sinifMevcutOndalikli(a, 0);
    float kusuratlarToplami = 0;

    for (int i = 0; i < a; i++) {
        kapasitelerToplami += sinifKapasite[i];
    }

    for (int i = 0; i < a; i++) {
        sinifMevcutOndalikli[i] = sinifKapasite[i] * ((float)ogrSayi / kapasitelerToplami);
        sinifMevcut[i] = (int)sinifMevcutOndalikli[i];
        kusuratlarToplami += sinifMevcutOndalikli[i] - sinifMevcut[i];
    }

    if (kusuratlarToplami > 0) {
        for (int i = 0; i < a; i++) {
            if (sinifMevcut[i] < sinifKapasite[i]) { // Kapasiteyi aşmamak için kontrol
                sinifMevcut[i]++;
                kusuratlarToplami--;
            }
            if (kusuratlarToplami <= 0)
                break;
        }
    }
}

// sirala fonksiyonu (büyükten küçüğe sıralama)
void sirala(vector<int>& sinifKapasite) {
    sort(sinifKapasite.rbegin(), sinifKapasite.rend());
}

// dagit fonksiyonu
void dagit(const vector<int>& sinifKapasite, const vector<int>& sinifMevcut) {
    vector<string> ad = { "alper", "deniz", "ozlem", "huseyin", "hulya", "didem",
                         "ajdar", "ayse", "mehmet", "husnu", "canan", "metin", "oksan" };
    vector<string> soyad = { "kaya", "san", "gurses", "yasar", "avsar",
                            "alkan", "anik", "sert", "andic", "yilmaz", "sahin", "kurt", "celik",
                            "boya", "huyuk", "guler", "sever", "ceylan" };

    vector<string> ekleAd = { "can", "gul", "nur", "su", "", "", "" };
    vector<string> ekleSoyad = { "oglu", "gil", "oz", "", "", "", "" };

    for (size_t i = 0; i < sinifKapasite.size(); i++) {
        if (sinifKapasite[i] == 0 || sinifMevcut[i] == 0) { // Boş sınıfları atla
            continue;
        }

        float ort = (float)100 * sinifMevcut[i] / sinifKapasite[i];
        cout << "\n\n" << sinifKapasite[i] << " kisilik sinifa " << sinifMevcut[i]
            << " kisi yerlestirildi.\nsinifin doluluk oranı: " << ort << " %dir." << endl;

        for (int k = 0; k < sinifMevcut[i]; k++) {
            string yeniIsim = ad[rand() % ad.size()] + ekleAd[rand() % ekleAd.size()];
            string yeniSoyisim = soyad[rand() % soyad.size()] + ekleSoyad[rand() % ekleSoyad.size()];
            int yil = rand() % 8;
            cout << (k + 1) << ". 05-0" << yil << "-" << rand() % 10 << rand() % 10 << rand() % 10 << rand() % 10
                << " " << yeniIsim << " " << yeniSoyisim << "\n";
        }
    }
}

int main() {
    srand(time(0)); // Rastgelelik için

    vector<int> sinifKapasite(5);
    vector<int> sinifMevcut(5, 0);
    int ogrSayi;
    int top;
    bool kntrl;

    do {
        top = 0;
        kntrl = false;
        cout << "Yerlestirilecek ogrenci sayisini giriniz: ";
        cin >> ogrSayi;

        if (cin.fail()) { // Geçersiz giriş kontrolü
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Hatali giris.\n";
            kntrl = true;
            continue;
        }

        if (ogrSayi < 100 || ogrSayi > 200) {
            cout << "Hatali giris. Ogrenci sayisi 100 ile 200 arasinda olmalidir.\n";
            kntrl = true;
            continue;
        }

        for (size_t i = 0; i < sinifKapasite.size(); i++) {
            cout << (i + 1) << ". sinifin kapasitesini giriniz: ";
            cin >> sinifKapasite[i];

            if (cin.fail() || sinifKapasite[i] < 0) { // Geçersiz giriş veya negatif kapasite kontrolü
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Hatali giris. Kapasite negatif olamaz.\n";
                kntrl = true;
                break;
            }

            top += sinifKapasite[i];
        }

        if (top < ogrSayi) {
            cout << "Hatali giris. Toplam kapasite ogrenci sayisindan kucuk olamaz.\n";
            kntrl = true;
        }

    } while (kntrl);

    sirala(sinifKapasite);
    dagilimBul(sinifKapasite, ogrSayi, sinifMevcut);
    dagit(sinifKapasite, sinifMevcut);

    return 0;
}
