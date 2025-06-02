#include <iostream>
#include <string>

using namespace std;

const int MAX_PASIEN = 100; //Batas maksimal pasien yang bisa ditampung

class Umum {
public:
    void menu();

private:
	// Struktur untuk menyimpan data pasien
    struct Pasien {
        string nama;
        int umur;
        string jenis_kelamin;
        string alamat;
        string telp;
        string keluhan;
        string poli;
    };

    Pasien daftar_pasien[MAX_PASIEN];
    int jumlah_pasien = 0;

    void pendaftaran_umum();
    void daftar_poli_umum();
    void keluhan_pasien();
    void tampilkan_data();
    void urutkan_data();
    void cari_data();
};

void Umum::pendaftaran_umum() {
    if (jumlah_pasien >= MAX_PASIEN) {
        cout << "Data pasien penuh.\n";
        return;
    }

    Pasien &p = daftar_pasien[jumlah_pasien];

    cout << "\nMasukkan Nama: ";
    cin.ignore();
    getline(cin, p.nama);

    cout << "Masukkan Umur: ";
    cin >> p.umur;

    cout << "Masukkan Jenis Kelamin (L/P): ";
    cin >> p.jenis_kelamin;

    cout << "Masukkan Nomor Telepon: ";
    cin >> p.telp;
    cin.ignore();

    cout << "Masukkan Alamat: ";
    getline(cin, p.alamat);

    ++jumlah_pasien;
}

void Umum::daftar_poli_umum() {
if (jumlah_pasien == 0) {
    cout << "Belum ada pasien terdaftar.\n";
    return;
}

cout << "\n=== PILIH POLI ===\n";
cout << "-------------------------------------------------------------\n";
cout << " 1. Klinik Anak\t\t\t  9. Klinik Syaraf\n";
cout << " 2. Klinik Kebidanan & Kandungan 10. Klinik Kulit & Kelamin\n";
cout << " 3. Klinik Penyakit Dalam\t 11. Klinik Mata\n";
cout << " 4. Klinik Bedah\t\t 12. Klinik Telinga, Hidung & Tenggorokan\n";
cout << " 5. Klinik Konsultan Bedah Digestif 13. Klinik Jiwa\n";
cout << " 6. Klinik Konsultan Bedah Onkologi 14. Klinik Jantung & Pembuluh Darah\n";
cout << " 7. Klinik Orthopedi\t\t 15. Klinik Gigi & Mulut\n";
cout << " 8. Klinik Urologi\n";
cout << "-------------------------------------------------------------\n";
cout << "Masukkan pilihan (1-15): ";

int pilihan;
cin >> pilihan;

string poli_terpilih;

switch (pilihan) {
    case 1:  
		poli_terpilih = "Klinik Anak"; 
		break;
    case 2:  
		poli_terpilih = "Klinik Kebidanan & Kandungan"; 
		break;
    case 3:  
		poli_terpilih = "Klinik Penyakit Dalam"; 
		break;
    case 4:  
		poli_terpilih = "Klinik Bedah"; 
		break;
    case 5:  
		poli_terpilih = "Klinik Konsultan Bedah Digestif"; 
		break;
    case 6:  
		poli_terpilih = "Klinik Konsultan Bedah Onkologi"; 
		break;
    case 7:  
		poli_terpilih = "Klinik Orthopedi"; 
		break;
    case 8:  
		poli_terpilih = "Klinik Urologi"; 
		break;
    case 9:  
		poli_terpilih = "Klinik Syaraf"; 
		break;
    case 10: 
		poli_terpilih = "Klinik Kulit & Kelamin"; 
		break;
    case 11: 
		poli_terpilih = "Klinik Mata"; 
		break;
    case 12: 
		poli_terpilih = "Klinik Telinga, Hidung & Tenggorokan"; 
		break;
    case 13: 
		poli_terpilih = "Klinik Jiwa"; 
		break;
    case 14: 
		poli_terpilih = "Klinik Jantung & Pembuluh Darah"; 
		break;
    case 15: 
	poli_terpilih = "Klinik Gigi & Mulut"; 
		break;
    default:
        cout << "Pilihan tidak valid.\n";
        return;
}

daftar_pasien[jumlah_pasien - 1].poli = poli_terpilih;
cout << "Poli berhasil dipilih: " << poli_terpilih << endl;
}

void Umum::keluhan_pasien() {
    if (jumlah_pasien == 0) {
        cout << "Belum ada pasien terdaftar.\n";
        return;
    }

    cout << "Masukkan Keluhan: ";
    cin.ignore();
    getline(cin, daftar_pasien[jumlah_pasien - 1].keluhan);
}

void Umum::tampilkan_data() {
    if (jumlah_pasien == 0) {
        cout << "Belum ada data pasien.\n";
        return;
    }

    for (int i = 0; i < jumlah_pasien; ++i) {
        Pasien &p = daftar_pasien[i];
        cout << "\nPasien ke-" << i + 1 << ":\n";
        cout << "Nama: " << p.nama << endl;
        cout << "Umur: " << p.umur << endl;
        cout << "Jenis Kelamin: " << p.jenis_kelamin << endl;
        cout << "Telepon: " << p.telp << endl;
        cout << "Alamat: " << p.alamat << endl;
        cout << "Keluhan: " << p.keluhan << endl;
        cout << "Poli: " << p.poli << endl;
    }
}

void Umum::urutkan_data() {
    if (jumlah_pasien == 0) {
        cout << "Belum ada data pasien.\n";
        return;
    }

    for (int i = 0; i < jumlah_pasien - 1; ++i) {
        for (int j = i + 1; j < jumlah_pasien; ++j) {
            if (daftar_pasien[i].nama > daftar_pasien[j].nama) {
                Pasien temp;

                temp.nama = daftar_pasien[i].nama;
                temp.umur = daftar_pasien[i].umur;
                temp.jenis_kelamin = daftar_pasien[i].jenis_kelamin;
                temp.alamat = daftar_pasien[i].alamat;
                temp.telp = daftar_pasien[i].telp;
                temp.keluhan = daftar_pasien[i].keluhan;
                temp.poli = daftar_pasien[i].poli;

                daftar_pasien[i].nama = daftar_pasien[j].nama;
                daftar_pasien[i].umur = daftar_pasien[j].umur;
                daftar_pasien[i].jenis_kelamin = daftar_pasien[j].jenis_kelamin;
                daftar_pasien[i].alamat = daftar_pasien[j].alamat;
                daftar_pasien[i].telp = daftar_pasien[j].telp;
                daftar_pasien[i].keluhan = daftar_pasien[j].keluhan;
                daftar_pasien[i].poli = daftar_pasien[j].poli;

                daftar_pasien[j].nama = temp.nama;
                daftar_pasien[j].umur = temp.umur;
                daftar_pasien[j].jenis_kelamin = temp.jenis_kelamin;
                daftar_pasien[j].alamat = temp.alamat;
                daftar_pasien[j].telp = temp.telp;
                daftar_pasien[j].keluhan = temp.keluhan;
                daftar_pasien[j].poli = temp.poli;
            }
        }
    }

    cout << "\nData telah diurutkan berdasarkan nama secara ascending.\n";
    tampilkan_data();
}


void Umum::cari_data() {
    if (jumlah_pasien == 0) {
        cout << "Belum ada data pasien.\n";
        return;
    }

    string keyword;
    cout << "Masukkan nama pasien yang ingin dicari: ";
    cin.ignore();
    getline(cin, keyword);

    bool ditemukan = false;
    for (int i = 0; i < jumlah_pasien; ++i) {
        if (daftar_pasien[i].nama == keyword) {
            cout << "\nData ditemukan:\n";
            cout << "Nama: " << daftar_pasien[i].nama << endl;
            cout << "Umur: " << daftar_pasien[i].umur << endl;
            cout << "Jenis Kelamin: " << daftar_pasien[i].jenis_kelamin << endl;
            cout << "Telepon: " << daftar_pasien[i].telp << endl;
            cout << "Alamat: " << daftar_pasien[i].alamat << endl;
            cout << "Keluhan: " << daftar_pasien[i].keluhan << endl;
            cout << "Poli: " << daftar_pasien[i].poli << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Data tidak ditemukan.\n";
    }
}

void Umum::menu() {
    int pilihan;

    do {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Pendaftaran Umum\n";
        cout << "2. Daftar Poli\n";
        cout << "3. Masukkan Keluhan\n";
        cout << "4. Tampilkan Semua Data\n"; 
        cout << "5. Urutkan Data\n";
        cout << "6. Cari Data\n";
        cout << "7. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        system("cls"); //untuk membersihkan layar sebelum menampilkan menu selanjutnya

        switch (pilihan) {
            case 1:
                pendaftaran_umum();
                break;
            case 2:
                daftar_poli_umum();
                break;
            case 3:
                keluhan_pasien();
                break;
            case 4:
                tampilkan_data();
                break;
            case 5:
                urutkan_data();
                break;
            case 6:
                cari_data();
                break;
            case 7:
                cout << "Terima kasih. Keluar...\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }

        if (pilihan != 7) {
            cout << "\nTekan Enter untuk kembali ke menu...";
            cin.ignore();
            cin.get();
        }

    } while (pilihan != 7);
}

// Fungsi main untuk menjalankan program
int main() {
    Umum app;
    app.menu();
    return 0;
}

