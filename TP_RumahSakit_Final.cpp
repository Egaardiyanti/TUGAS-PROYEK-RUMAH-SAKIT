#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <limits>

using namespace std;

// Struktur data Pasien umum dan BPJS
struct PasienUmum {
    string nama;
    int umur;
    char jenis_kelamin;
    string telp;
    string alamat;
    string keluhan;
    string poli;
    string jenis_rawat_umum;
};

struct PasienBpjs {
    string namaBpjs;
    int umurBpjs;
    char jenis_kelamin_Bpjs;
    string tel_Bpjs;
    string alamatBpjs;
    string keluhanBpjs;
    string poliBpjs;
    string jenis_rawat_bpjs;
};

// Class IGD
class PasienIGD {
private:
    string nama;
    int umur;
    string alamat;
    string keluhan;
    string nomorRekamMedis;
    string tingkatKedaruratan;
    string dokterMenangani;

public:	
    void inputData();
    void tampilkanData();
    string getNomorRekamMedis();
    void simpanKeFile(ofstream &file);
};

const int MAX_PASIEN = 100;
const int JUMLAH_DOKTER = 5;

string daftarDokter[JUMLAH_DOKTER] = {
    "dr. Ega Ardiyanti, Sp.BTKV",
    "dr. Devalya Lameysha Manurung, Sp.EM",
    "dr. Armondha Ayesha Shakila, Sp.JP",
    "dr. Lestari Dewi, Sp.EM",
    "dr. Bagas Wicaksono, Sp.EM"
};

class SistemIGD {
private:
    PasienIGD daftarPasien[MAX_PASIEN];
    int jumlahPasien;

public:
    SistemIGD() : jumlahPasien(0) {}
    void tambahPasien();
    void tampilkanSemuaPasien();
    void cariPasien();
    void menu();
};

void PasienIGD::inputData() {
    cout << "\nMasukkan Nama Pasien       : ";
    getline(cin, nama);
    cout << "Masukkan Umur              : ";
    cin >> umur;
    cin.ignore();
    cout << "Masukkan Alamat            : ";
    getline(cin, alamat);
    cout << "Masukkan Keluhan           : ";
    getline(cin, keluhan);
    cout << "Masukkan Nomor Rekam Medis : ";
    getline(cin, nomorRekamMedis);

    // Pilih tingkat kedaruratan
    int pilihKedaruratan;
    bool inputValid = false;

    do {
        cout << "\nPilih Tingkat Kedaruratan:\n";
        cout << "1. Ringan\n";
        cout << "2. Sedang\n";
        cout << "3. Berat\n";
        cout << "Masukkan pilihan (1-3): ";
        cin >> pilihKedaruratan;
        cin.ignore();

        switch (pilihKedaruratan) {
            case 1:
                tingkatKedaruratan = "Ringan";
                inputValid = true;
                break;
            case 2:
                tingkatKedaruratan = "Sedang";
                inputValid = true;
                break;
            case 3:
                tingkatKedaruratan = "Berat";
                inputValid = true;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan masukkan angka 1-3.\n";
        }
    } while (!inputValid);

    // Pilih dokter
    cout << "\nPilih Dokter yang Menangani:\n";
    for (int i = 0; i < JUMLAH_DOKTER; i++) {
        cout << i + 1 << ". " << daftarDokter[i] << endl;
    }
    int pilihan;
    cout << "Masukkan nomor pilihan dokter (1-" << JUMLAH_DOKTER << "): ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan >= 1 && pilihan <= JUMLAH_DOKTER) {
        dokterMenangani = daftarDokter[pilihan - 1];
    } else {
        dokterMenangani = "Tidak diketahui";
    }
}

void PasienIGD::tampilkanData() {
	cout << "===========================================\n";
    cout << "               Data Pasien IGD             \n";
    cout << "===========================================\n";
    cout << "Nama             : " << nama << endl;
    cout << "Umur             : " << umur << endl;
    cout << "Alamat           : " << alamat << endl;
    cout << "Keluhan          : " << keluhan << endl;
    cout << "No Rekam Medis   : " << nomorRekamMedis << endl;
    cout << "Kedaruratan      : " << tingkatKedaruratan << endl;
    cout << "Dokter Menangani : " << dokterMenangani << endl;
}

string PasienIGD::getNomorRekamMedis() {
    return nomorRekamMedis;
}

void PasienIGD::simpanKeFile(ofstream &file) {
    file << nama << endl;
    file << umur << endl;
    file << alamat << endl;
    file << keluhan << endl;
    file << nomorRekamMedis << endl;
    file << tingkatKedaruratan << endl;
    file << dokterMenangani << endl;
    file << "---------------------------------" << endl;
}

void SistemIGD::tambahPasien() {
    if (jumlahPasien < MAX_PASIEN) {
    	cout << "===========================================\n";
        cout << "           Pendaftaran Pasien IGD          \n";
        cout << "===========================================\n";
        cin.ignore();
        daftarPasien[jumlahPasien].inputData();
        ofstream myfile("data_pasien_igd.txt", ios::app);
    if (!myfile) {
        cout << "Gagal membuka file untuk menyimpan data.\n";
        return;
    }

    daftarPasien[jumlahPasien].simpanKeFile(myfile);
    myfile.close();

    ++jumlahPasien;
    cout << "\nPasien berhasil didaftarkan.\n";
	
	    } else {
        cout << "\nData pasien sudah penuh!\n";
    }
}

void SistemIGD::tampilkanSemuaPasien() {
    if (jumlahPasien == 0) {
        cout << "\nBelum ada pasien yang terdaftar.\n";
    } else {
        for (int i = 0; i < jumlahPasien; i++) {
            daftarPasien[i].tampilkanData();
        }
    }
}

void SistemIGD::cariPasien() {
    string cariRekamMedis;
    char ulangi;
    bool ditemukan = false;

    do {
        cout << "\nMasukkan Nomor Rekam Medis yang dicari: ";
        cin.ignore();
        getline(cin, cariRekamMedis);

        ditemukan = false;

        for (int i = 0; i < jumlahPasien; i++) {
            if (daftarPasien[i].getNomorRekamMedis() == cariRekamMedis) {
                cout << "\nPasien ditemukan!";
                daftarPasien[i].tampilkanData();
                ditemukan = true;
                break;
            }
        }

        if (!ditemukan) {
            cout << "\nPasien dengan nomor tersebut tidak ditemukan.\n";
            cout << "Apakah ingin mencari lagi? (y/n): ";
            cin >> ulangi;
            cin.ignore();
        } else {
            break;
        }

    } while (ulangi == 'y' || ulangi == 'Y');

    if (!ditemukan) {
        cout << "\nPasien belum melakukan pendaftaran atau bukan pasien rumah sakit.\n";
    }
}

void SistemIGD::menu() {
    int pilihan;

    do {
    	cout << "===========================================\n";
        cout << "             Sistem Manajemen IGD          \n";
        cout << "===========================================\n";
        cout << "1. Daftar Pasien IGD\n";
        cout << "2. Tampilkan Semua Pasien\n";
        cout << "3. Cari Pasien\n";
        cout << "4. Keluar\n";
        cout << "Pilih menu (1-4): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahPasien();
                break;
            case 2:
                tampilkanSemuaPasien();
                break;
            case 3:
                cariPasien();
                break;
            case 4:
                cout << "\nTerima kasih. Program selesai.\n";
                break;
            default:
                cout << "\nPilihan tidak valid. Coba lagi.\n";
        }

    } while (pilihan != 4);
}

// Class Rawat Inap
class Rawatinap {
private:
    const int biayaRawatInap = 100000;
    const int biayaAdmin = 20000;
    int jumlahBayar;
    int jumlahHari;

public:
    void prosesPembayaran();
    void rincian();
    void struk();
    void setJumlahBayar(int bayar) { jumlahBayar = bayar; }
    void setJumlahHari(int hari) { jumlahHari = hari; }
};

// Class Rawat Jalan
class Rawatjalan {
private:
    const int biayaRawatJalan = 50000;
    const int biayaAdmin2 = 15000;
    int jumlahBayar2;
    int jumlahHari2;

public:
    void prosesPembayaran();
    void rincian2();
    void struk2();
    void setJumlahBayar2(int bayar2) { jumlahBayar2 = bayar2; }
    void setJumlahHari2(int hari2) { jumlahHari2 = hari2; }
};

void Rawatinap::prosesPembayaran() {
	cout << "===========================================\n";
    cout << "              BIAYA RAWAT INAP             \n";
    cout << "===========================================\n";
    cout << "Biaya Rawat Inap per Hari : Rp " << biayaRawatInap << endl;
    cout << "Biaya Admin               : Rp " << biayaAdmin << endl;

    cout << "Masukkan jumlah hari perawatan: ";
    while (!(cin >> jumlahHari) || jumlahHari <= 0) {
        cout << "Mohon masukkan angka hari yang valid (>0): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int total = (biayaRawatInap * jumlahHari) + biayaAdmin;
    cout << "Total                     : Rp " << total << endl;

    int bayar;
    cout << "Masukkan jumlah pembayaran Anda: Rp ";
    while (!(cin >> bayar) || bayar < 0) {
        cout << "Mohon masukkan angka pembayaran yang valid (>=0): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    setJumlahBayar(bayar);
    setJumlahHari(jumlahHari);

    rincian();
}

void Rawatinap::rincian() {
    int total = (biayaRawatInap * jumlahHari) + biayaAdmin;
    int kembalian = jumlahBayar - total;
	cout << "===========================================\n";
    cout << "       RINCIAN PEMBAYARAN (Rawat Inap)     \n";
    cout << "===========================================\n";
    cout << "Jumlah Hari      : " << jumlahHari << " hari\n";
    cout << "Biaya Rawat Inap : Rp " << biayaRawatInap << " x " << jumlahHari << endl;
    cout << "Biaya Admin      : Rp " << biayaAdmin << endl;
    cout << "Total            : Rp " << total << endl;
    cout << "Jumlah Bayar     : Rp " << jumlahBayar << endl;
    cout << "Kembalian        : Rp " << kembalian << endl;

    int pil;
    do {
        cout << "\n1. Cetak Struk\n2. Kembali ke Menu Pasien\n3. Keluar\n";
        cout << "Masukkan Pilihan Anda : ";
        cin >> pil;

        switch (pil) {
            case 1:
                struk();
                break;
            case 2:
                return;
            case 3:
                cout << "Terima kasih, program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pil != 3);
}

void Rawatinap::struk() {
    time_t waktu;
    time(&waktu);
    int total = (biayaRawatInap * jumlahHari) + biayaAdmin;
    int kembalian = jumlahBayar - total;


	cout << "===========================================\n";
    cout << "              STRUK RAWAT INAP             \n";
    cout << "===========================================\n";
    cout << "Tanggal/Waktu : " << ctime(&waktu);
    cout << "Jumlah Hari   : " << jumlahHari << " hari\n";
    cout << "Biaya Inap    : Rp " << biayaRawatInap << " x " << jumlahHari << endl;
    cout << "Admin         : Rp " << biayaAdmin << endl;
    cout << "Total         : Rp " << total << endl;
    cout << "Bayar         : Rp " << jumlahBayar << endl;
    cout << "Kembalian     : Rp " << kembalian << endl;
	cout << "===========================================\n";
	}

void Rawatjalan::prosesPembayaran() {
	cout << "===========================================\n";
    cout << "              BIAYA RAWAT JALAN            \n";
    cout << "===========================================\n";
    cout << "Biaya Rawat Jalan per Hari : Rp " << biayaRawatJalan << endl;
    cout << "Biaya Admin                : Rp " << biayaAdmin2 << endl;

    cout << "Masukkan jumlah hari kunjungan: ";
    while (!(cin >> jumlahHari2) || jumlahHari2 <= 0) {
        cout << "Mohon masukkan angka hari yang valid (>0): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int total2 = (biayaRawatJalan * jumlahHari2) + biayaAdmin2;
    cout << "Total                      : Rp " << total2 << endl;

    int bayar2;
    cout << "Masukkan jumlah pembayaran Anda: Rp ";
    while (!(cin >> bayar2) || bayar2 < 0) {
        cout << "Mohon masukkan angka pembayaran yang valid (>=0): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    setJumlahBayar2(bayar2);
    setJumlahHari2(jumlahHari2);

    rincian2();
}

void Rawatjalan::rincian2() {
    int total2 = (biayaRawatJalan * jumlahHari2) + biayaAdmin2;
    int kembalian2 = jumlahBayar2 - total2;
	cout << "===========================================\n";
    cout << "      RINCIAN PEMBAYARAN (Rawat Jalan)     \n";
    cout << "===========================================\n";
    cout << "Jumlah Hari      : " << jumlahHari2 << " hari\n";
    cout << "Biaya Rawat Jalan: Rp " << biayaRawatJalan << " x " << jumlahHari2 << endl;
    cout << "Biaya Admin      : Rp " << biayaAdmin2 << endl;
    cout << "Total            : Rp " << total2 << endl;
    cout << "Jumlah Bayar     : Rp " << jumlahBayar2 << endl;
    cout << "Kembalian        : Rp " << kembalian2 << endl;
	cout << "===========================================\n";
    int pil;
    do {
        cout << "\n1. Cetak Struk\n2. Kembali ke Menu Pasien\n3. Keluar\n";
        cout << "Masukkan Pilihan Anda : ";
        cin >> pil;

        switch (pil) {
            case 1:
                struk2();
                break;
            case 2:
                return;
            case 3:
                cout << "Terima kasih, program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pil != 3);
}

void Rawatjalan::struk2() {
    time_t waktu;
    time(&waktu);
    int total2 = (biayaRawatJalan * jumlahHari2) + biayaAdmin2;
    int kembalian2 = jumlahBayar2 - total2;
	cout << "===========================================\n";
    cout << "              STRUK RAWAT JALAN            \n";
    cout << "===========================================\n";
    cout << "Tanggal/Waktu : " << ctime(&waktu);
    cout << "Jumlah Hari   : " << jumlahHari2 << " hari\n";
    cout << "Biaya Jalan   : Rp " << biayaRawatJalan << " x " << jumlahHari2 << endl;
    cout << "Admin         : Rp " << biayaAdmin2 << endl;
    cout << "Total         : Rp " << total2 << endl;
    cout << "Bayar         : Rp " << jumlahBayar2 << endl;
    cout << "Kembalian     : Rp " << kembalian2 << endl;
	cout << "===========================================\n";
	}
	
// Class Lab dan Sistem Laboratorium
const int MAKS_PASIEN = 100;

class PasienLab {
private:
    string nama;
    string rekamMedis;
    string jenisLab;
    string keluhan;
    string tanggalTes;
    string hasilTes;

public:
    string getRekamMedis() { return rekamMedis; }
    string getJenisLab() { return jenisLab; }
    string getHasilTes() { return hasilTes; }
    string getNama() { return nama; }
    string getTanggalTes() { return tanggalTes; }

    void inputData();
    void tampilkanData();
};

void PasienLab::inputData() {
    cout << "Nama Pasien                  : ";
    getline(cin, nama);
    cout << "Nomor Rekam Medis            : ";
    getline(cin, rekamMedis);
    cout << "Tanggal Tes (dd-mm-yyyy)     : ";
    getline(cin, tanggalTes);

    int pilihanLab;
    bool inputValid2 = false;
    do {
        cout << "Pilih Jenis Laboratorium:\n";
        cout << "1. Patologi Klinik\n";
        cout << "2. Mikrobiologi\n";
        cout << "3. Patologi Anatomi\n";
        cout << "Masukkan Pilihan Anda (1-3) : ";
        cin >> pilihanLab;
        cin.ignore();

        switch (pilihanLab) {
            case 1:
                jenisLab = "Patologi Klinik";
                inputValid2 = true;
                break;
            case 2:
                jenisLab = "Mikrobiologi";
                inputValid2 = true;
                break;
            case 3:
                jenisLab = "Patologi Anatomi";
                inputValid2 = true;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan masukkan angka (1-3)!!" << endl;
        }
    } while (!inputValid2);

    cout << "Keluhan atau Keterangan Tambahan : ";
    getline(cin, keluhan);
    cout << "Hasil Tes                        : ";
    getline(cin, hasilTes);

    cout << "Pendaftaran berhasil.\n";
    cout << "-------------------------------\n";
}

void PasienLab::tampilkanData() {
	cout << "===========================================\n";
    cout << "Nama Pasien       : " << nama << endl;
    cout << "No. Rekam Medis   : " << rekamMedis << endl;
    cout << "Tanggal Tes       : " << tanggalTes << endl;
    cout << "Jenis Lab         : " << jenisLab << endl;
    cout << "Keluhan           : " << keluhan << endl;
    cout << "Hasil Tes         : " << hasilTes << endl;
	cout << "===========================================\n";
}

class SistemLaboratorium {
private:
    PasienLab daftarPasien[MAKS_PASIEN];
    int jumlahPasien;

public:
    SistemLaboratorium() : jumlahPasien(0) {}

    void daftarPasienLab();
    void tampilkanPasienPerLab();
    void tampilkanSemuaPasien();
    void cariDataPasien();
    void tampilkanHasilTes();
    void menu();
};

void SistemLaboratorium::daftarPasienLab() {
    if (jumlahPasien < MAKS_PASIEN) {
        cin.ignore();
        cout << "===========================================\n";
        cout << "        Input Data Pasien Laboratorium     \n";
        cout << "===========================================\n";
        daftarPasien[jumlahPasien].inputData();
        jumlahPasien++;
        cout << "Data pasien berhasil ditambahkan.\n";
    } else {
        cout << "Kapasitas penuh, tidak dapat menambah data pasien.\n";
    }
}

void SistemLaboratorium::tampilkanPasienPerLab() {
    string jenisLab;
    int pilihan;
	cout << "===========================================\n";
    cout << "Pilih Jenis Laboratorium untuk ditampilkan:\n";
    cout << "1. Patologi Klinik\n";
    cout << "2. Mikrobiologi\n";
    cout << "3. Patologi Anatomi\n";
    cout << "===========================================\n";
    cout << "Masukkan Pilihan Anda: ";
    cin >> pilihan;
    cin.ignore();

    switch (pilihan) {
        case 1: jenisLab = "Patologi Klinik"; break;
        case 2: jenisLab = "Mikrobiologi"; break;
        case 3: jenisLab = "Patologi Anatomi"; break;
        default:
            cout << "Pilihan tidak valid!\n";
            return;
    }
	cout << "===========================================\n";
    cout << "      Daftar Pasien di Laboratorium " << jenisLab << "    \n";
    cout << "===========================================\n";
    bool ditemukan = false;
    for (int i = 0; i < jumlahPasien; i++) {
        if (daftarPasien[i].getJenisLab() == jenisLab) {
            daftarPasien[i].tampilkanData();
            ditemukan = true;
        }
    }
    if (!ditemukan) {
        cout << "Belum ada pasien di jenis lab ini.\n";
    }
}

void SistemLaboratorium::tampilkanSemuaPasien() {
    if (jumlahPasien == 0) {
        cout << "Belum ada data pasien.\n";
        return;
    }
	cout << "===========================================\n";
    cout << "    Daftar Seluruh Pasien Laboratorium:    \n";
    cout << "===========================================\n";
    for (int i = 0; i < jumlahPasien; i++) {
        daftarPasien[i].tampilkanData();
    }
}

void SistemLaboratorium::cariDataPasien() {
    if (jumlahPasien == 0) {
        cout << "Belum ada data pasien.\n";
        return;
    }
    string cariRekamMedis;
    cin.ignore();
    cout << "Masukkan Nomor Rekam Medis yang dicari: ";
    getline(cin, cariRekamMedis);

    bool ditemukan = false;
    for (int i = 0; i < jumlahPasien; i++) {
        if (cariRekamMedis == daftarPasien[i].getRekamMedis()) {
            daftarPasien[i].tampilkanData();
            ditemukan = true;
            return;
        }
    }
    if (!ditemukan) {
        cout << "Data pasien dengan nomor rekam medis tersebut tidak ditemukan.\n";
    }
}

void SistemLaboratorium::tampilkanHasilTes() {
    if (jumlahPasien == 0) {
        cout << "Belum ada data pasien.\n";
        return;
    }
    cout << "===========================================\n";
    cout << "    Daftar Hasil Tes Laboratorium Pasien   \n";
    cout << "===========================================\n";
    for (int i = 0; i < jumlahPasien; i++) {
        cout << "Nama Pasien       : " << daftarPasien[i].getNama() << endl;
        cout << "Nomor Rekam Medis : " << daftarPasien[i].getRekamMedis() << endl;
        cout << "Tanggal Tes       : " << daftarPasien[i].getTanggalTes() << endl;
        cout << "Jenis Lab         : " << daftarPasien[i].getJenisLab() << endl;
        cout << "Hasil Tes         : " << daftarPasien[i].getHasilTes() << endl;
        cout << "===========================================\n";
    }
}

void SistemLaboratorium::menu() {
    int pilihan;

    do {
    	cout << "===========================================\n";
        cout << "      Sistem Rumah Sakit - Laboratorium    \n";
        cout << "===========================================\n";
        cout << "1. Daftar Pasien Laboratorium\n";
        cout << "2. Tampilkan Pasien per Jenis Lab\n";
        cout << "3. Tampilkan Semua Pasien\n";
        cout << "4. Cari Data Pasien\n";
        cout << "5. Tampilkan Hasil Tes Pasien\n";
        cout << "6. Keluar\n";
        cout << "===========================================\n";
        cout << "Pilihan Anda (1-6): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                daftarPasienLab();
                break;
            case 2:
                tampilkanPasienPerLab();
                break;
            case 3:
                tampilkanSemuaPasien();
                break;
            case 4:
                cariDataPasien();
                break;
            case 5:
                tampilkanHasilTes();
                break;
            case 6:
                cout << "Terima kasih telah menggunakan sistem.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 6);
}

// Class Obat dan Sistem Farmasi
const int MAX_OBAT = 100;

class Obat {
private:
    int kode;
    string nama;
    int stok;
    int harga;

public:
    Obat() {}
    Obat(int k, string n, int s, int h) : kode(k), nama(n), stok(s), harga(h) {}

    void inputObat();
    void tampilObat();
    string getNama();
    int getStok();
    int getHarga();
    void kurangiStok(int jumlah);
};

class SistemFarmasi {
private:
    Obat daftarObat[MAX_OBAT];
    int jumlahObat = 0;
    string obatTerakhir;
    int jumlahTerakhir = 0;
    int hargaTerakhir = 0;
    int totalTerakhir = 0;
    int dibayar = 0;
    int kembalian = 0;
    bool transaksiSelesai = false;
    int bayar;

public:
    void dataObat();
    void tambahObat();
    void tampilkanObat();
    void pengambilanObat();
    void cetakResi();
    void pembayaran();
	void cetakStruk();
	void menu();
    void menumenu();
};

void Obat::inputObat() {
    cout << "Masukkan kode obat   : ";
    cin >> kode;
    cin.ignore();
    cout << "Masukkan nama obat   : ";
    getline(cin, nama);
    cout << "Masukkan stok obat   : ";
    cin >> stok;
    cout << "Masukkan harga obat  : ";
    cin >> harga;
}

void Obat::tampilObat() {
    cout << "===========================================\n";
    cout << "Kode : " << kode << endl;
    cout << "Nama : " << nama << endl;
    cout << "Stok : " << stok << endl;
    cout << "Harga: Rp" << harga << endl;
    cout << "===========================================\n";
}

string Obat::getNama() { return nama; }
int Obat::getStok() { return stok; }
int Obat::getHarga() { return harga; }
void Obat::kurangiStok(int jumlah) {
    if (jumlah <= stok) stok -= jumlah;
}

void SistemFarmasi::dataObat() {
    daftarObat[jumlahObat++] = Obat(101, "Paracetamol", 100, 1000);
    daftarObat[jumlahObat++] = Obat(102, "Amoksisilin", 80, 5000);
    daftarObat[jumlahObat++] = Obat(103, "Metformin", 90, 3000);
    daftarObat[jumlahObat++] = Obat(104, "Salbutamol Inhaler", 50, 50000);
    daftarObat[jumlahObat++] = Obat(105, "Omeprazol", 70, 10000);
    daftarObat[jumlahObat++] = Obat(106, "Insulin", 40, 150000);
    daftarObat[jumlahObat++] = Obat(107, "Diazepam", 60, 7000);
    daftarObat[jumlahObat++] = Obat(108, "Ceftriaxone", 30, 50000);
    daftarObat[jumlahObat++] = Obat(109, "Furosemid", 65, 6000);
    daftarObat[jumlahObat++] = Obat(110, "Vitamin C", 120, 2000);
}

void SistemFarmasi::tampilkanObat() {
	cout << "===========================================\n";
    cout << "         DATA OBAT TERSEDIA SAAT INI       \n";
    cout << "===========================================\n";
    if (jumlahObat == 0) {
        cout << "Belum ada data obat.\n";
        return;
    }
    for (int i = 0; i < jumlahObat; i++) {
        daftarObat[i].tampilObat();
    }
}

void SistemFarmasi::tambahObat() {
    char pilihTambah = 'y';

    while (pilihTambah == 'y' || pilihTambah == 'Y') {
        if (jumlahObat < MAX_OBAT) {
        	cout << "===========================================\n";
            cout << "                 Tambah Obat               \n";
            cout << "===========================================\n";
            daftarObat[jumlahObat].inputObat();
            jumlahObat++;
            cout << "Data Obat telah ditambahkan.\n";
        } else {
            cout << "Data obat penuh. Tidak bisa menambahkan lebih banyak.\n";
            break;
        }

        cout << "\nApakah Anda ingin menambahkan obat baru? (y/n): ";
        cin >> pilihTambah;
    }
	cout << "===========================================\n";
    cout << "       DAFTAR OBAT SETELAH PENAMBAHAN      \n";
    cout << "===========================================\n";
    for (int i = 0; i < jumlahObat; i++) {
        daftarObat[i].tampilObat();
    }
}

void SistemFarmasi::pengambilanObat() {
    string namaObat;
    int jumlahAmbil;

    cin.ignore();
    cout << "===========================================\n";
    cout << "Masukkan nama obat yang diambil : ";
    getline(cin, namaObat);
    cout << "Masukkan jumlah yang diambil    : ";
    cin >> jumlahAmbil;
	cout << "===========================================\n";
    if (jumlahAmbil <= 0) {
        cout << "Jumlah tidak valid.\n";
        return;
    }

    bool obatDitemukan = false;
    for (int i = 0; i < jumlahObat; i++) {
        if (daftarObat[i].getNama() == namaObat) {
            obatDitemukan = true;
            if (daftarObat[i].getStok() >= jumlahAmbil) {
                daftarObat[i].kurangiStok(jumlahAmbil);
                obatTerakhir = namaObat;
                jumlahTerakhir = jumlahAmbil;
                hargaTerakhir = daftarObat[i].getHarga();
                totalTerakhir = jumlahAmbil * hargaTerakhir;
                cout << "Obat berhasil diberikan.\n";
                cout << "Total biaya obat: Rp" << totalTerakhir << endl;
            } else {
                cout << "Stok tidak mencukupi. Stok tersedia: " << daftarObat[i].getStok() << endl;
            }
            break;
        }
    }

    if (!obatDitemukan) {
        cout << "Obat tidak ditemukan.\n";
    }
}

void SistemFarmasi::cetakResi() {
    if (totalTerakhir == 0) {
        cout << "Belum ada transaksi yang dilakukan.\n";
        return;
    }
	cout << "===========================================\n";
    cout << "              RESI PESANAN OBAT            \n";
    cout << "===========================================\n";
    cout << "Nama Obat : " << obatTerakhir << endl;
    cout << "Jumlah    : " << jumlahTerakhir << endl;
    cout << "Harga Satuan : Rp" << hargaTerakhir << endl;
    cout << "Total     : Rp" << totalTerakhir << endl;
    cout << "===========================================\n";
}

void SistemFarmasi::pembayaran() {
    if (totalTerakhir == 0) {
        cout << "Belum ada transaksi yang dilakukan.\n";
        return;
    }

    cout << "===========================================\n";
    cout << "                 PEMBAYARAN                \n";
    cout << "===========================================\n";
    cout << "Total yang harus dibayar: Rp" << totalTerakhir << endl;
    cout << "Masukkan jumlah uang     : Rp";
    cin >> bayar;

    if (bayar < totalTerakhir) {
        cout << "Uang tidak cukup. Transaksi dibatalkan.\n";
        return;
    }

    kembalian = bayar - totalTerakhir;
}

void SistemFarmasi::cetakStruk() {
    if (!transaksiSelesai) {
        cout << "Belum ada pembayaran yang dilakukan.\n";
        return;
    }

    cout << "===========================================\n";
    cout << "              STRUK PEMBAYARAN             \n";
    cout << "===========================================\n";
    cout << "Obat      : " << obatTerakhir << endl;
    cout << "Jumlah    : " << jumlahTerakhir << endl;
    cout << "Total     : Rp" << totalTerakhir << endl;
    cout << "Dibayar   : Rp" << dibayar << endl;
    cout << "Kembalian : Rp" << kembalian << endl;
    cout << "===========================================\n";

    // Reset transaksi setelah struk dicetak
    totalTerakhir = 0;
    dibayar = 0;
    kembalian = 0;
    transaksiSelesai = false;
}


void SistemFarmasi::menu() {
    int pilihan;
    do {
    	cout << "===========================================\n";
        cout << "       MENU SISTEM FARMASI RUMAH SAKIT     \n";
        cout << "===========================================\n";
        cout << "1. Tambah Pesanan Obat\n";
        cout << "2. Tampilkan Obat\n";
        cout << "3. Pengambilan Obat oleh Pasien\n";
        cout << "4. Cetak Resi Pesanan\n";
        cout << "5. Pembayaran\n";
		cout << "6. Cetak Struk\n";
        cout << "7. Keluar\n";
        cout << "===========================================\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: 
				tambahObat(); 
				break;
            case 2: 
				tampilkanObat(); 
				break;
            case 3: 
				pengambilanObat(); 
				break;
            case 4: 
				cetakResi(); 
				break;
            case 5: 
				pembayaran(); 
				break;
            case 6: 
				cetakStruk(); 
				break;
            case 7: 
				cout << "Terima kasih telah menggunakan sistem farmasi.\n"; 
				break;
            default: 
				cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 7);
}

void SistemFarmasi::menumenu() {
    SistemFarmasi sistem;
    sistem.dataObat();
    sistem.tampilkanObat();
    sistem.menu();
}

// Class untuk pasien umum dengan satu menu terintegrasi
class PasienUmumMenu {
private:
    PasienUmum pasien_umum;
    bool memilikiJenisRawat = false;

public:
    void pendaftaran_umum();
    void daftar_poli_umum();
    void input_keluhan_umum();
    bool pilih_jenis_rawat_umum();
    void simpan_data_umum();
    void cari_data_umum();
    void proses_pembayaran_umum();
    void menu();
};

void PasienUmumMenu::pendaftaran_umum() {
	cout << "===========================================\n";
    cout << "          Pendaftaran Pasien Umum          \n";
    cout << "===========================================\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nama\t\t: ";
    getline(cin, pasien_umum.nama);
    cout << "Umur\t\t: ";
    while (!(cin >> pasien_umum.umur) || pasien_umum.umur < 0 || pasien_umum.umur > 150) {
        cout << "Masukkan umur valid (0-150): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Jenis Kelamin (L/P)\t: ";
    cin >> pasien_umum.jenis_kelamin;
    pasien_umum.jenis_kelamin = toupper(pasien_umum.jenis_kelamin);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Alamat\t\t: ";
    getline(cin, pasien_umum.alamat);
    cout << "No.Telepon\t\t: ";
    getline(cin, pasien_umum.telp);
    memilikiJenisRawat = false; // reset jenis rawat if you newly register
}

void PasienUmumMenu::daftar_poli_umum() {
    if (pasien_umum.nama.empty()) {
        cout << "Silakan lakukan pendaftaran terlebih dahulu.\n";
        return;
    }
    cout << "===========================================\n";
    cout << "            Pilih Poli Pasien Umum         \n";
	cout << "===========================================\n";
    cout << " 1. Klinik Anak\n";
    cout << " 2. Klinik Kebidanan & Kandungan\n";
    cout << " 3. Klinik Penyakit Dalam\n";
    cout << " 4. Klinik Bedah\n";
    cout << " 5. Klinik Konsultan Bedah Digestif\n";
    cout << " 6. Klinik Konsultan Bedah Onkologi\n";
    cout << " 7. Klinik Orthopedi\n";
    cout << " 8. Klinik Urologi\n";
    cout << " 9. Klinik Syaraf\n";
    cout << "10. Klinik Kulit & Kelamin\n";
    cout << "11. Klinik Mata\n";
    cout << "12. Klinik Telinga, Hidung & Tenggorokan\n";
    cout << "13. Klinik Jiwa\n";
    cout << "14. Klinik Jantung & Pembuluh Darah\n";
    cout << "15. Klinik Gigi & Mulut\n";
	cout << "===========================================\n";
    cout << "Masukkan pilihan (1-15): ";

    int pilihan;
    cin >> pilihan;

    switch (pilihan) {
        case 1: 
			pasien_umum.poli = "Klinik Anak"; 
			break;
        case 2: 
			pasien_umum.poli = "Klinik Kebidanan & Kandungan"; 
			break;
        case 3: 
			pasien_umum.poli = "Klinik Penyakit Dalam"; 
			break;
        case 4: 
			pasien_umum.poli = "Klinik Bedah"; 
			break;
        case 5: 
			pasien_umum.poli = "Klinik Konsultan Bedah Digestif"; 
			break;
        case 6: 
			pasien_umum.poli = "Klinik Konsultan Bedah Onkologi"; 
			break;
        case 7: 
			pasien_umum.poli = "Klinik Orthopedi"; 
			break;
        case 8: 
			pasien_umum.poli = "Klinik Urologi"; 
			break;
        case 9: 
			pasien_umum.poli = "Klinik Syaraf"; 
			break;
        case 10: 
			pasien_umum.poli = "Klinik Kulit & Kelamin"; 
			break;
        case 11: 
			pasien_umum.poli = "Klinik Mata"; 
			break;
        case 12: 
			pasien_umum.poli = "Klinik Telinga, Hidung & Tenggorokan"; 
			break;
        case 13: 
			pasien_umum.poli = "Klinik Jiwa"; 
			break;
        case 14: 
			pasien_umum.poli = "Klinik Jantung & Pembuluh Darah"; 
			break;
        case 15: 
			pasien_umum.poli = "Klinik Gigi & Mulut"; 
			break;
        default:
            cout << "Pilihan tidak valid.\n";
            pasien_umum.poli = "";
            return;
    }

    cout << "\nPoli berhasil dipilih : " << pasien_umum.poli << "\n";
}

void PasienUmumMenu::input_keluhan_umum() {
    if (pasien_umum.nama.empty()) {
        cout << "Silakan lakukan pendaftaran terlebih dahulu.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan Keluhan Anda: ";
    getline(cin, pasien_umum.keluhan);
}

bool PasienUmumMenu::pilih_jenis_rawat_umum() {
    if (pasien_umum.nama.empty()) {
        cout << "Silakan lakukan pendaftaran terlebih dahulu.\n";
        return false;
    }
    int jenis_rawat_umum;
    do {
    	cout << "===========================================\n";
        cout << "          Pilih Jenis Layanan Rawat:       \n";
        cout << "===========================================\n";
        cout << "1. Rawat Jalan\n";
        cout << "2. Rawat Inap\n";
        cout << "3. Lewati / Kembali\n";
        cout << "===========================================\n";
        cout << "Masukkan pilihan: ";
        cin >> jenis_rawat_umum;

        switch (jenis_rawat_umum) {
            case 1:
                pasien_umum.jenis_rawat_umum = "Rawat Jalan";
                memilikiJenisRawat = true;
                return true;
            case 2:
                pasien_umum.jenis_rawat_umum = "Rawat Inap";
                memilikiJenisRawat = true;
                return true;
            case 3:
                pasien_umum.jenis_rawat_umum = "";
                memilikiJenisRawat = false;
                return false;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (true);
}

void PasienUmumMenu::simpan_data_umum() {
    if (pasien_umum.nama.empty()) {
        cout << "Data belum lengkap. Silakan lakukan pendaftaran terlebih dahulu.\n";
        return;
    }
    ofstream file("data_pasien_umum.txt", ios::app);
    if (file.is_open()) {
        file << pasien_umum.nama << endl;
        file << pasien_umum.umur << endl;
        file << pasien_umum.jenis_kelamin << endl;
        file << pasien_umum.alamat << endl;
        file << pasien_umum.telp << endl;
        file << pasien_umum.keluhan << endl;
        file << pasien_umum.poli << endl;
        file << pasien_umum.jenis_rawat_umum << endl;
        file << "===\n";
        file.close();
        cout << "Data berhasil disimpan.\n";
    } else {
        cout << "Gagal membuka file.\n";
    }
}

void PasienUmumMenu::cari_data_umum() {
    ifstream file("data_pasien_umum.txt");
    if (!file) {
        cout << "File tidak ditemukan.\n";
        return;
    }

    string nama_cari;
    cout << "Masukkan nama pasien yang dicari: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nama_cari);

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line == nama_cari) {
            found = true;
            cout << "===========================================\n";
            cout << "        Data Ditemukan Pasien Umum:        \n";
            cout << "===========================================\n";
            cout << "Nama: " << line << endl;
            string umur, jenisKelamin, alamat, telp, keluhan, poli, jenis_rawat_umum;
            getline(file, umur);
            getline(file, jenisKelamin);
            getline(file, alamat);
            getline(file, telp);
            getline(file, keluhan);
            getline(file, poli);
            getline(file, jenis_rawat_umum);
            cout << "Umur: " << umur << endl;
            cout << "Jenis Kelamin: " << jenisKelamin << endl;
            cout << "Alamat: " << alamat << endl;
            cout << "Telepon: " << telp << endl;
            cout << "Keluhan: " << keluhan << endl;
            cout << "Poli: " << poli << endl;
            cout << "Jenis Layanan Rawat : " << jenis_rawat_umum << endl;
            cout << "===========================================\n";
            break;
        }
    }
    if (!found) {
        cout << "Data tidak ditemukan.\n";
    }
    file.close();
}

void PasienUmumMenu::proses_pembayaran_umum() {
    if (!memilikiJenisRawat) {
        cout << "Silakan pilih jenis layanan rawat terlebih dahulu pada menu 4.\n";
        return;
    }
    if (pasien_umum.jenis_rawat_umum == "Rawat Jalan") {
        Rawatjalan rj;
        rj.prosesPembayaran();
    } else if (pasien_umum.jenis_rawat_umum == "Rawat Inap") {
        Rawatinap ri;
        ri.prosesPembayaran();
    } else {
        cout << "Jenis layanan rawat tidak valid.\n";
    }
}

void PasienUmumMenu::menu() {
    int pilihan;
    do {
    	cout << "===========================================\n";
        cout << "               MENU PASIEN UMUM            \n";
    	cout << "===========================================\n";
        cout << "1. Pendaftaran\n";
        cout << "2. Pilih Poli\n";
        cout << "3. Masukkan Keluhan\n";
        cout << "4. Pilih Jenis Layanan Rawat\n";
        cout << "5. Proses Pembayaran\n";
        cout << "6. Simpan Data\n";
        cout << "7. Cari Data\n";
        cout << "8. Kembali ke Menu Utama\n";
        cout << "===========================================\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                pendaftaran_umum();
                break;
            case 2:
                daftar_poli_umum();
                break;
            case 3:
                input_keluhan_umum();
                break;
            case 4:
                pilih_jenis_rawat_umum();
                break;
            case 5:
                proses_pembayaran_umum();
                break;
            case 6:
                simpan_data_umum();
                break;
            case 7:
                cari_data_umum();
                break;
            case 8:
                cout << "Kembali ke menu utama...\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 8);
}

// Class untuk pasien BPJS dengan menu terintegrasi
class PasienBPJSMenu {
private:
    PasienBpjs pasien_bpjs;
    bool memilikiJenisRawat = false;

public:
    void pendaftaran();
    void daftar_poli_bpjs();
    void input_keluhan_bpjs();
    bool pilih_jenis_rawat_bpjs();
    void simpan_data();
    void tampilkan_data();
    void cari_data();
    void proses_pembayaran_bpjs();
    void menu();
};

void PasienBPJSMenu::pendaftaran() {
	cout << "===========================================\n";
    cout << "          Pendaftaran Pasien BPJS          \n";
   	cout << "===========================================\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nama\t\t: ";
    getline(cin, pasien_bpjs.namaBpjs);
    cout << "Umur\t\t: ";
    while (!(cin >> pasien_bpjs.umurBpjs) || pasien_bpjs.umurBpjs < 0 || pasien_bpjs.umurBpjs > 150) {
        cout << "Masukkan umur valid (0-150): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Jenis Kelamin (L/P)\t: ";
    cin >> pasien_bpjs.jenis_kelamin_Bpjs;
    pasien_bpjs.jenis_kelamin_Bpjs = toupper(pasien_bpjs.jenis_kelamin_Bpjs);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Alamat\t\t: ";
    getline(cin, pasien_bpjs.alamatBpjs);
    cout << "No.Telepon\t\t: ";
    getline(cin, pasien_bpjs.tel_Bpjs);
    memilikiJenisRawat = false; // reset jenis rawat on new registration
}

void PasienBPJSMenu::daftar_poli_bpjs() {
    if (pasien_bpjs.namaBpjs.empty()) {
        cout << "Silakan lakukan pendaftaran terlebih dahulu.\n";
        return;
    }
    cout << "===========================================\n";
    cout << "           Pilih Poli Pasien BPJS          \n";
    cout << "===========================================\n";
    cout << " 1. Klinik Anak\n";
    cout << " 2. Klinik Kebidanan & Kandungan\n";
    cout << " 3. Klinik Penyakit Dalam\n";
    cout << " 4. Klinik Bedah\n";
    cout << " 5. Klinik Konsultan Bedah Digestif\n";
    cout << " 6. Klinik Konsultan Bedah Onkologi\n";
    cout << " 7. Klinik Orthopedi\n";
    cout << " 8. Klinik Urologi\n";
    cout << " 9. Klinik Syaraf\n";
    cout << "10. Klinik Kulit & Kelamin\n";
    cout << "11. Klinik Mata\n";
    cout << "12. Klinik Telinga, Hidung & Tenggorokan\n";
    cout << "13. Klinik Jiwa\n";
    cout << "14. Klinik Jantung & Pembuluh Darah\n";
    cout << "15. Klinik Gigi & Mulut\n";
	cout << "===========================================\n";
    cout << "Masukkan pilihan (1-15): ";

    int pilihan;
    cin >> pilihan;

    switch (pilihan) {
        case 1: 
			pasien_bpjs.poliBpjs = "Klinik Anak"; 
			break;
        case 2: 
			pasien_bpjs.poliBpjs = "Klinik Kebidanan & Kandungan"; 
			break;
        case 3: 
			pasien_bpjs.poliBpjs = "Klinik Penyakit Dalam"; 
			break;
        case 4: 
			pasien_bpjs.poliBpjs = "Klinik Bedah"; 
			break;
        case 5: 
			pasien_bpjs.poliBpjs = "Klinik Konsultan Bedah Digestif"; 
			break;
        case 6: 
			pasien_bpjs.poliBpjs = "Klinik Konsultan Bedah Onkologi"; 
			break;
        case 7: 
			pasien_bpjs.poliBpjs = "Klinik Orthopedi"; 
			break;
        case 8: 
			pasien_bpjs.poliBpjs = "Klinik Urologi"; 
			break;
        case 9: 
			pasien_bpjs.poliBpjs = "Klinik Syaraf"; 
			break;
        case 10: 
			pasien_bpjs.poliBpjs = "Klinik Kulit & Kelamin"; 
			break;
        case 11: 
			pasien_bpjs.poliBpjs = "Klinik Mata"; 
			break;
        case 12: 
			pasien_bpjs.poliBpjs = "Klinik Telinga, Hidung & Tenggorokan"; 
			break;
        case 13: 
			pasien_bpjs.poliBpjs = "Klinik Jiwa"; 
			break;
        case 14: 
			pasien_bpjs.poliBpjs = "Klinik Jantung & Pembuluh Darah"; 
			break;
        case 15: 
			pasien_bpjs.poliBpjs = "Klinik Gigi & Mulut"; 
			break;
        default:
            cout << "Pilihan tidak valid.\n";
            pasien_bpjs.poliBpjs = "";
            return;
    }

    cout << "\nPoli berhasil dipilih : " << pasien_bpjs.poliBpjs << "\n";
}

void PasienBPJSMenu::input_keluhan_bpjs() {
    if (pasien_bpjs.namaBpjs.empty()) {
        cout << "Silakan lakukan pendaftaran terlebih dahulu.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan Keluhan Anda: ";
    getline(cin, pasien_bpjs.keluhanBpjs);
}

bool PasienBPJSMenu::pilih_jenis_rawat_bpjs() {
    if (pasien_bpjs.namaBpjs.empty()) {
        cout << "Silakan lakukan pendaftaran terlebih dahulu.\n";
        return false;
    }
    int rawat_bpjs;
    do {
    	cout << "===========================================\n";
        cout << "   Pilih Jenis Layanan Rawat Pasien BPJS:  \n";
        cout << "===========================================\n";
        cout << "1. Rawat Jalan\n";
        cout << "2. Rawat Inap\n";
        cout << "3. Lewati / Kembali\n";
        cout << "===========================================\n";
        cout << "Masukkan pilihan Anda : ";
        cin >> rawat_bpjs;

        switch (rawat_bpjs) {
            case 1:
                pasien_bpjs.jenis_rawat_bpjs = "Rawat Jalan";
                memilikiJenisRawat = true;
                return true;
            case 2:
                pasien_bpjs.jenis_rawat_bpjs = "Rawat Inap";
                memilikiJenisRawat = true;
                return true;
            case 3:
                pasien_bpjs.jenis_rawat_bpjs = "";
                memilikiJenisRawat = false;
                return false;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (true);
}

void PasienBPJSMenu::simpan_data() {
    if (pasien_bpjs.namaBpjs.empty()) {
        cout << "Data belum lengkap. Silakan lakukan pendaftaran terlebih dahulu.\n";
        return;
    }
    ofstream data("data_pasien_bpjs.txt", ios::app);
    if (data.is_open()) {
        data << pasien_bpjs.namaBpjs << endl;
        data << pasien_bpjs.umurBpjs << endl;
        data << pasien_bpjs.jenis_kelamin_Bpjs << endl;
        data << pasien_bpjs.alamatBpjs << endl;
        data << pasien_bpjs.tel_Bpjs << endl;
        data << pasien_bpjs.keluhanBpjs << endl;
        data << pasien_bpjs.poliBpjs << endl;
        data << pasien_bpjs.jenis_rawat_bpjs << endl;
        data << "===\n";
        data.close();
        cout << "Data berhasil disimpan.\n";
    } else {
        cout << "Gagal membuka file.\n";
    }
}

void PasienBPJSMenu::tampilkan_data() {
    ifstream data("data_pasien_bpjs.txt");
    string baris;

    if (!data.is_open()) {
        cout << "File data tidak ditemukan.\n";
        return;
    }
	cout << "===========================================\n";
    cout << "            Daftar Pasien BPJS             \n";
    cout << "===========================================\n";
    while (getline(data, baris)) {
        cout << baris << endl;
    }
    data.close();
}

void PasienBPJSMenu::cari_data() {
    ifstream data("data_pasien_bpjs.txt");
    if (!data) {
        cout << "File tidak ditemukan.\n";
        return;
    }

    string cari_nama;
    cout << "Masukkan nama pasien yang dicari: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, cari_nama);

    string baris;
    bool ditemukan = false;
    while (getline(data, baris)) {
        if (baris == cari_nama) {
            ditemukan = true;
            cout << "===========================================\n";
            cout << "          Data Ditemukan Pasien BPJS:      \n";
            cout << "===========================================\n";
            cout << "Nama: " << baris << endl;
            string umurBpjs, jenis_kelamin_bpjs, alamatBpjs, telpBpjs, keluhanBpjs, poliBpjs, jenis_rawat_bpjs;
            getline(data, umurBpjs);
            getline(data, jenis_kelamin_bpjs);
            getline(data, alamatBpjs);
            getline(data, telpBpjs);
            getline(data, keluhanBpjs);
            getline(data, poliBpjs);
            getline(data, jenis_rawat_bpjs);
            cout << "Umur: " << umurBpjs << endl;
            cout << "Jenis Kelamin: " << jenis_kelamin_bpjs << endl;
            cout << "Alamat: " << alamatBpjs << endl;
            cout << "Telepon: " << telpBpjs << endl;
            cout << "Keluhan: " << keluhanBpjs << endl;
            cout << "Poli: " << poliBpjs << endl;
            cout << "Jenis Layanan Rawat : " << jenis_rawat_bpjs << endl;
            cout << "===========================================\n";
            break;
        }
    }

    if (!ditemukan) {
        cout << "Data pasien tidak ditemukan.\n";
    }

    data.close();
}

void PasienBPJSMenu::proses_pembayaran_bpjs() {
    if (!memilikiJenisRawat) {
        cout << "Silakan pilih jenis layanan rawat terlebih dahulu pada menu 4.\n";
        return;
    }
    if (pasien_bpjs.jenis_rawat_bpjs == "Rawat Jalan") {
        Rawatjalan rj;
        rj.prosesPembayaran();
    } else if (pasien_bpjs.jenis_rawat_bpjs == "Rawat Inap") {
        Rawatinap ri;
        ri.prosesPembayaran();
    } else {
        cout << "Jenis layanan rawat tidak valid.\n";
    }
}

void PasienBPJSMenu::menu() {
    int pilihan;
    do {
    	cout << "===========================================\n";
        cout << "              MENU PASIEN BPJS             \n";
        cout << "===========================================\n";
        cout << "1. Pendaftaran\n";
        cout << "2. Daftar Poli\n";
        cout << "3. Masukkan Keluhan\n";
        cout << "4. Pilih Jenis Layanan Rawat\n";
        cout << "5. Proses Pembayaran\n";
        cout << "6. Simpan Data\n";
        cout << "7. Tampilkan Semua Data\n";
        cout << "8. Cari Data\n";
        cout << "9. Kembali ke Menu Utama\n";
        cout << "===========================================\n";
        cout << "Masukkan Pilihan : ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                pendaftaran();
                break;
            case 2:
                daftar_poli_bpjs();
                break;
            case 3:
                input_keluhan_bpjs();
                break;
            case 4:
                pilih_jenis_rawat_bpjs();
                break;
            case 5:
                proses_pembayaran_bpjs();
                break;
            case 6:
                simpan_data();
                break;
            case 7:
                tampilkan_data();
                break;
            case 8:
                cari_data();
                break;
            case 9:
                cout << "Kembali ke menu utama...\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 9);
}

// Class Pasien menu utama dengan login dan daftar pasien baru
class Pasien {
public:
    string nama, idPasien, jenisKelamin, alamat, password;
    int umur;

    void tampilkan() {
        cout << "Nama          : " << nama << endl;
        cout << "ID Pasien     : " << idPasien << endl;
        cout << "Umur          : " << umur << endl;
        cout << "Jenis Kelamin : " << jenisKelamin << endl;
        cout << "Alamat        : " << alamat << endl;
    }

    void simpanKeFile() {
        ofstream file("pasien.txt", ios::app);
        file << nama << ";" << idPasien << ";" << umur << ";" << jenisKelamin << ";" << alamat << ";" << password << "\n";
        file.close();
    }

    static string buatIDBaru() {
        ifstream file("pasien.txt");
        string baris, idTerakhir = "RM0000";

        while (getline(file, baris)) {
            stringstream ss(baris);
            string tempNama, tempId;
            getline(ss, tempNama, ';');
            getline(ss, tempId, ';');
            idTerakhir = tempId;
        }
        file.close();

        int nomor = 0;
        if (idTerakhir.size() >= 2) {
            string angkaStr = idTerakhir.substr(2);
            stringstream(angkaStr) >> nomor;
        }
        nomor++;

        stringstream ss;
        ss << "RM" << setfill('0') << setw(4) << nomor;
        return ss.str();
    }

    static bool loginPasien(const string &idInput, const string &passInput, Pasien &hasil) {
        ifstream file("pasien.txt");
        string baris;
        while (getline(file, baris)) {
            stringstream ss(baris);
            string umurStr;
            getline(ss, hasil.nama, ';');
            getline(ss, hasil.idPasien, ';');
            getline(ss, umurStr, ';');
            stringstream(umurStr) >> hasil.umur;
            getline(ss, hasil.jenisKelamin, ';');
            getline(ss, hasil.alamat, ';');
            getline(ss, hasil.password, ';');
            if (hasil.idPasien == idInput && hasil.password == passInput) {
                return true;
            }
        }
        return false;
    }

    static void tampilkanSemua() {
        ifstream file("pasien.txt");
        string baris;
        int no = 1;
        while (getline(file, baris)) {
            stringstream ss(baris);
            Pasien p;
            string umurStr;
            getline(ss, p.nama, ';');
            getline(ss, p.idPasien, ';');
            getline(ss, umurStr, ';');
            stringstream(umurStr) >> p.umur;
            getline(ss, p.jenisKelamin, ';');
            getline(ss, p.alamat, ';');
            getline(ss, p.password, ';');

            cout << "\nPasien ke-" << no++ << ":\n";
            p.tampilkan();
        }
    }

    static void editPasien(const string &idEdit) {
        ifstream file("pasien.txt");
        ofstream temp("temp.txt");
        string baris;
        bool ditemukan = false;

        while (getline(file, baris)) {
            stringstream ss(baris);
            Pasien p;
            string umurStr;
            getline(ss, p.nama, ';');
            getline(ss, p.idPasien, ';');
            getline(ss, umurStr, ';');
            stringstream(umurStr) >> p.umur;
            getline(ss, p.jenisKelamin, ';');
            getline(ss, p.alamat, ';');
            getline(ss, p.password, ';');

            if (p.idPasien == idEdit) {
                ditemukan = true;
                cout << "Data baru untuk ID " << idEdit << ":\n";
                cout << "Nama          : "; getline(cin, p.nama);
                cout << "Umur          : "; cin >> p.umur; cin.ignore();
                cout << "Jenis Kelamin : "; getline(cin, p.jenisKelamin);
                cout << "Alamat        : "; getline(cin, p.alamat);
                cout << "Password      : "; getline(cin, p.password);
            }

            temp << p.nama << ";" << p.idPasien << ";" << p.umur << ";" << p.jenisKelamin << ";" << p.alamat << ";" << p.password << "\n";
        }
        file.close();
        temp.close();
        remove("pasien.txt");
        rename("temp.txt", "pasien.txt");

        if (ditemukan) cout << "Data berhasil diedit.\n";
        else cout << "ID tidak ditemukan.\n";
    }

    static void hapusPasien(const string &idHapus) {
        ifstream file("pasien.txt");
        ofstream temp("temp.txt");
        string baris;
        bool ditemukan = false;

        while (getline(file, baris)) {
            stringstream ss(baris);
            string nama, idPasien;
            getline(ss, nama, ';');
            getline(ss, idPasien, ';');
            if (idPasien == idHapus) {
                ditemukan = true;
                continue;
            }
            temp << baris << "\n";
        }
        file.close();
        temp.close();
        remove("pasien.txt");
        rename("temp.txt", "pasien.txt");

        if (ditemukan) cout << "Pasien berhasil dihapus.\n";
        else cout << "ID tidak ditemukan.\n";
    }

    static void cariPasien(const string &kata) {
        ifstream file("pasien.txt");
        string baris;
        bool ketemu = false;
        while (getline(file, baris)) {
            if (baris.find(kata) != string::npos) {
                ketemu = true;
                stringstream ss(baris);
                Pasien p;
                string umurStr;
                getline(ss, p.nama, ';');
                getline(ss, p.idPasien, ';');
                getline(ss, umurStr, ';');
                stringstream(umurStr) >> p.umur;
                getline(ss, p.jenisKelamin, ';');
                getline(ss, p.alamat, ';');
                getline(ss, p.password, ';');

                cout << "\nDitemukan:\n";
                p.tampilkan();
            }
        }
        if (!ketemu) cout << "Data tidak ditemukan.\n";
    }
};

bool loginAdmin(const string &user, const string &pass) {
    return user == "admin" && pass == "admin123";
}

void menuAdmin() {
    string user, pass;
    cout << "Username : ";
    getline(cin, user);
    cout << "Password : ";
    getline(cin, pass);
    if (loginAdmin(user, pass)) {
        cout << "\nLogin admin berhasil.\n";
        int menu;
        do {
        	cout << "===========================================\n";
            cout << "                  MENU ADMIN               \n";
            cout << "===========================================\n";
            cout << "1. Tambah Pasien\n";
            cout << "2. Tampilkan Semua\n";
            cout << "3. Edit Pasien\n";
            cout << "4. Hapus Pasien\n";
            cout << "5. Cari Pasien\n";
            cout << "6. Logout\n";
            cout << "===========================================\n";
            cout << "Pilih: ";
            cin >> menu;
            cin.ignore();
            switch (menu) {
                case 1: {
                    Pasien p;
                    cout << "Nama          : ";
                    getline(cin, p.nama);
                    p.idPasien = Pasien::buatIDBaru();
                    cout << "Umur          : ";
                    cin >> p.umur;
                    cin.ignore();
                    cout << "Jenis Kelamin : ";
                    getline(cin, p.jenisKelamin);
                    cout << "Alamat        : ";
                    getline(cin, p.alamat);
                    cout << "Password      : ";
                    getline(cin, p.password);
                    p.simpanKeFile();
                    cout << "Data berhasil disimpan dengan ID: " << p.idPasien << "\n";
                    break;
                }
                case 2: Pasien::tampilkanSemua(); 
					break;
                case 3: {
                    string id;
                    cout << "Masukkan ID pasien: ";
                    getline(cin, id);
                    Pasien::editPasien(id);
                    break;
                }
                case 4: {
                    string id;
                    cout << "Masukkan ID pasien: ";
                    getline(cin, id);
                    Pasien::hapusPasien(id);
                    break;
                }
                case 5: {
                    string id;
                    cout << "Masukkan ID pasien: ";
                    getline(cin, id);
                    Pasien::cariPasien(id);
                    break;
                }
                default:
                    if (menu != 6) cout << "Pilihan tidak valid.\n";
            }
        } while (menu != 6);
    } else {
        cout << "Login gagal.\n";
    }
}

void informasi() {
		cout << "===========================================\n";
		cout << "            INFORMASI RUMAH SAKIT          \n";
		cout << "===========================================\n";
		cout << "Alamat    : Jl. Wirosaban No.1 Yogyakarta 55162\n";
		cout << "Telepon   : (0274) 123-4567\n";
		cout << "Layanan   : Gawat Darurat, Rawat Inap, \n"
		     << "            Rawat Jalan, Laboratorium, Apotek\n";
		cout << "-------------------------------------------\n";
		cout << "PENDAFTARAN LOKET:\n";
		cout << "  Layanan Pagi:\n";
		cout << "    Senin - Kamis    : 07.15 - 11.00\n";
		cout << "    Jum'at - Sabtu   : 07.15 - 10.00\n";
		cout << "  Layanan Sore:\n";
		cout << "    Senin - Kamis    : 12.00 - 16.00\n";
		cout << "    Jum'at           : 13.00 - 16.00\n";
		cout << "    Sabtu            : 11.00 - 14.00\n";
		cout << "-------------------------------------------\n";
		cout << "PERATURAN KUNJUNGAN PASIEN:\n";
		cout << "  1. Pengunjung berusia 12 tahun ke atas\n";
		cout << "  2. Pengunjung dalam kondisi sehat\n";
		cout << "  3. Tetap menerapkan protokol kesehatan\n"
		     << "     (menggunakan masker dan cuci tangan)\n";
		cout << "  4. Pengunjung masuk ke ruang pasien secara\n"
		     << "     terbatas dan bergantian\n";
		
}

//class kasir
class Kasir {
	Rawatinap inap;
    Rawatjalan jalan;
    SistemFarmasi farmasi;
public :
void menuKasir() {
        int pilihan;
        do {
            cout << "\n=== MENU KASIR ===\n";
            cout << "1. Rawat Inap\n";
            cout << "2. Rawat Jalan\n";
            cout << "3. Farmasi\n";
            cout << "0. Keluar\n";
            cout << "Pilih: ";
            cin >> pilihan;

            switch (pilihan) {
                case 1: 
					inap.struk(); 
					break;
                case 2: 
					jalan.struk2(); 
					break;
                case 3: 
					farmasi.cetakStruk(); 
					break;
                case 0: 
					cout << "Keluar dari menu kasir\n"; 
					break;
                default: 
					cout << "Pilihan tidak valid\n"; 
					break;
            }
        } while (pilihan != 0);
    }
};

void menuPasien() {
    int opsi;
    do {
    	cout << "===========================================\n";
        cout << "                 MENU PASIEN               \n";
        cout << "===========================================\n";
        cout << "1. Login Pasien\n";
        cout << "2. Daftar Pasien Baru\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> opsi;
        cin.ignore();

        switch (opsi) {
            case 1: {
                Pasien p;
                string id, pass;
                cout << "ID Pasien : ";
                getline(cin, id);
                cout << "Password  : ";
                getline(cin, pass);
                if (Pasien::loginPasien(id, pass, p)) {
                    cout << "\nLogin berhasil.\n";
                    cout << "--- Data Anda ---\n";
                    p.tampilkan();

                    int layanan;
                    do {
                    	cout << "===========================================\n";
                        cout << "                Sistem Layanan             \n";
                        cout << "===========================================\n";
                        cout << "1. IGD\n";
                        cout << "2. UMUM\n";
						cout << "3. BPJS\n";
						cout << "4. Laboratorium\n";
						cout << "5. Farmasi\n";
						cout << "6. Kasir\n";
						cout << "7. Keluar\n";
                        cout << "Masukkan Pilihan : ";
                        cin >> layanan;
                        cin.ignore();
                        switch (layanan) {
                            case 1: {
                                SistemIGD igd;
                                igd.menu();
                                break;
                            }
                            case 2: {
                                PasienUmumMenu pasien_umum;
                                pasien_umum.menu();
                                break;
                            }
                            case 3: {
                                PasienBPJSMenu pasien_bpjs;
                                pasien_bpjs.menu();
                                break;
                            }
                            case 4: {
                                SistemLaboratorium lab;
                                lab.menu();
                                break;
                            }
                            case 5: {
                                SistemFarmasi farmasi;
                                farmasi.menumenu();
                                break;
                            }
                            case 6:{
                            	Kasir kasir;
                                kasir.menuKasir();
								break;
							}
                            case 7:
                                cout << "Terima kasih telah menggunakan sistem.\n";
                                break;
                            default:
                                cout << "Pilihan tidak valid.\n";
                        }
                    } while (layanan != 7);
                } else {
                    cout << "Login gagal. ID atau password salah.\n";
                }
                break;
            }
            case 2: {
                Pasien p;
                cout << "===========================================\n";
                cout << "           Pendaftaran Pasien Baru         \n";
                cout << "===========================================\n";
                cout << "Nama          : ";
                getline(cin, p.nama);
                p.idPasien = Pasien::buatIDBaru();
                cout << "Umur          : ";
                cin >> p.umur;
                cin.ignore();
                cout << "Jenis Kelamin : ";
                getline(cin, p.jenisKelamin);
                cout << "Alamat        : ";
                getline(cin, p.alamat);
                cout << "Password      : ";
                getline(cin, p.password);
                p.simpanKeFile();
                cout << "Pendaftaran berhasil. ID Anda: " << p.idPasien << "\n";
                break;
            }
            case 0:
                cout << "Kembali ke menu utama.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (opsi != 0);
}

int main() {
    int pilihan;
    do {
	    
    	cout << "===========================================\n";
        cout << "                MENU UTAMA                 \n";
        cout << "===========================================\n";
        cout << "1. Login Admin\n";
        cout << "2. Menu Pasien\n";
        cout << "3. Informasi Rumah Sakit\n";
        cout << "4. Keluar\n";
        cout << "===========================================\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                menuAdmin();
                break;
            case 2:
                menuPasien();
                break;
            case 3:
                informasi();
                break;
            case 4:
                cout << "Terima kasih.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 4);

    return 0;
}
