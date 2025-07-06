#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// PASIEN
class Pasien{
public:
  string nama;
  string idPasien;
  string nik;
  string tempatLahir;
  string tanggalLahir;
  string golDarah;
  string jenisKelamin;
  string alamat;
  string noHP;
  int umur;

  void tampilkan();
  void simpanKeFile();
  static string buatIDBaru();
  static bool loginPasien(const string &idInput, const string &passInput, Pasien &hasil);
  static void tampilkanSemua();
  static void editPasien(const string &idEdit);
  static void hapusPasien(const string &idHapus);
  static void cariPasien();
  static void urutkanPasien(int mode, bool ascending);
};

void Pasien::tampilkan(){
  cout << "+======================================================================+\n";
  cout << "| Nama                     : " << left << setw(40) << nama << "|\n";
  cout << "| ID Pasien                : " << left << setw(40) << idPasien << "|\n";
  cout << "| NIK                      : " << left << setw(40) << nik << "|\n";
  cout << "| Jenis Kelamin            : " << left << setw(40) << jenisKelamin << "|\n";
  cout << "| Tempat Lahir             : " << left << setw(40) << tempatLahir << "|\n";
  cout << "| Tanggal Lahir (DD-MM-YY) : " << left << setw(40) << tanggalLahir << "|\n";
  cout << "| Golongan Darah           : " << left << setw(40) << golDarah << "|\n";
  cout << "| Alamat                   : " << left << setw(40) << alamat << "|\n";
  cout << "| Nomor HP                 : " << left << setw(40) << noHP << "|\n";
  cout << "| Umur                     : " << left << setw(40) << umur << "|\n";
  cout << "+=====================================================================+\n";
}


void Pasien::simpanKeFile(){
  ofstream file("pasien.txt", ios::app);
  file << nama << ";" << idPasien << ";" << nik << ";" << tempatLahir << ";" << tanggalLahir << ";"
       << golDarah << ";" << jenisKelamin << ";" << alamat << ";" << noHP << ";" << umur << ";\n";
  file.close();
}

string Pasien::buatIDBaru(){
  ifstream file("pasien.txt");
  string baris, idTerakhir = "RM0000";

  while (getline(file, baris)){
    stringstream ss(baris);
    string tempNama, tempId;
    getline(ss, tempNama, ';');
    getline(ss, tempId, ';');
    idTerakhir = tempId;
  }
  file.close();

  int nomor = 0;
  if (idTerakhir.size() >= 2){
    string angkaStr = idTerakhir.substr(2);
    stringstream(angkaStr) >> nomor;
  }
  nomor++;

  stringstream ss;
  ss << "RM" << setfill('0') << setw(4) << nomor;
  return ss.str();
}

void Pasien::tampilkanSemua(){
  ifstream file("pasien.txt");
  string baris;
  int i = 1;

  while (getline(file, baris))  {
    stringstream ss(baris);
    Pasien p;
    string umurStr;

    getline(ss, p.nama, ';');
    getline(ss, p.idPasien, ';');
    getline(ss, p.nik, ';');
    getline(ss, p.tempatLahir, ';');
    getline(ss, p.tanggalLahir, ';');
    getline(ss, p.golDarah, ';');
    getline(ss, p.jenisKelamin, ';');
    getline(ss, p.alamat, ';');
    getline(ss, p.noHP, ';');
    getline(ss, umurStr, ';');
    stringstream(umurStr) >> p.umur;

    cout << "\n+======================================================+\n";
    cout << "|                  DATA PASIEN KE " << i++ <<"             |\n";
    p.tampilkan();
  }
}

void Pasien::editPasien(const string &idEdit)
{
  ifstream file("pasien.txt");
  ofstream temp("temp.txt");
  string baris;
  bool ditemukan = false;

  while (getline(file, baris))
  {
    stringstream ss(baris);
    Pasien p;
    string umurStr;

    getline(ss, p.nama, ';');
    getline(ss, p.idPasien, ';');
    getline(ss, p.nik, ';');
    getline(ss, p.tempatLahir, ';');
    getline(ss, p.tanggalLahir, ';');
    getline(ss, p.golDarah, ';');
    getline(ss, p.jenisKelamin, ';');
    getline(ss, p.alamat, ';');
    getline(ss, p.noHP, ';');
    getline(ss, umurStr, ';');
    stringstream(umurStr) >> p.umur;

    if (p.idPasien == idEdit)
    {
      ditemukan = true;
      cout << "---------Data baru untuk ID " << idEdit << "----------\n";
      cout << "Nama                    : ";
      getline(cin, p.nama);
      cout << "NIK                     : ";
      getline(cin, p.nik);
      cout << "Tempat Lahir            : ";
      getline(cin, p.tempatLahir);
      cout << "Tanggal Lahir(DD-MM-DD) : ";
      getline(cin, p.tanggalLahir);
      cout << "No HP                   : ";
      getline(cin, p.noHP);
      cout << "Golongan Darah          : ";
      getline(cin, p.golDarah);
      cout << "Umur                    : ";
      cin >> p.umur;
      cin.ignore();
      cout << "Jenis Kelamin           : ";
      getline(cin, p.jenisKelamin);
      cout << "Alamat                  : ";
      getline(cin, p.alamat);
      cin.ignore();
    }

    temp << p.nama << ";" << p.idPasien << ";" << p.nik << ";" << p.tempatLahir << ";" << p.tanggalLahir << ";"
     << p.golDarah << ";" << p.jenisKelamin << ";" << p.alamat << ";" << p.noHP << ";" << p.umur << ";\n";
  }

  file.close();
  temp.close();
  remove("pasien.txt");
  rename("temp.txt", "pasien.txt");

  if (ditemukan)
    cout << "Data berhasil diedit.\n";
  else
    cout << "ID tidak ditemukan.\n";
}

void Pasien::hapusPasien(const string &idHapus)
{
  ifstream file("pasien.txt");
  ofstream temp("temp.txt");
  string baris;
  bool ditemukan = false;

  while (getline(file, baris))
  {
    stringstream ss(baris);
    string nama, idPasien;
    getline(ss, nama, ';');
    getline(ss, idPasien, ';');
    if (idPasien == idHapus)
    {
      ditemukan = true;
      continue;
    }
    temp << baris << "\n";
  }

  file.close();
  temp.close();
  remove("pasien.txt");
  rename("temp.txt", "pasien.txt");

  if (ditemukan)
    cout << "Pasien berhasil dihapus.\n";
  else
    cout << "ID tidak ditemukan.\n";
}

void Pasien::cariPasien()
{
  Pasien data[100];
  int jumlah = 0;
  ifstream file("pasien.txt");
  string baris;

  while (getline(file, baris) && jumlah < 100)
  {
    stringstream ss(baris);
    string umurStr;

    getline(ss, data[jumlah].nama, ';');
    getline(ss, data[jumlah].idPasien, ';');
    getline(ss, data[jumlah].nik, ';');
    getline(ss, data[jumlah].tempatLahir, ';');
    getline(ss, data[jumlah].tanggalLahir, ';');
    getline(ss, data[jumlah].jenisKelamin, ';');
    getline(ss, data[jumlah].golDarah, ';');
    getline(ss, data[jumlah].alamat, ';');
    getline(ss, data[jumlah].noHP, ';');
    getline(ss, umurStr, ';');
    stringstream(umurStr) >> data[jumlah].umur;

    jumlah++;
  }
  file.close();

  int cari;
  cout << "\n=== MENU PENCARIAN PASIEN ===\n";
  cout << "1. Searching ID Pasien\n";
  cout << "2. Searching Nama Pasien\n";
  cout << "3. Searching Umur Pasien\n";
  cout << "Masukkan Pilihan : ";
  cin >> cari;
  cin.ignore();

  bool ditemukan = false;

  if (cari == 1)
  {
    string cariID;
    cout << "\nMasukkan ID pasien (contohnya RM0001) : ";
    getline(cin, cariID);
    for (int i = 0; i < jumlah; i++)
    {
      if (data[i].idPasien == cariID)
      {
        cout << "\n------Data Pasien ditemukan------\n";
        data[i].tampilkan();
        ditemukan = true;
      }
    }
  }
  else if (cari == 2)
  {
    string cariNama;
    cout << "\nMasukkan nama pasien (boleh sebagian) : ";
    getline(cin, cariNama);
    for (int i = 0; i < jumlah; i++)
    {
      if (data[i].nama.find(cariNama) != string::npos)
      {
        cout << "\n------Data Pasien ditemukan------\n";
        data[i].tampilkan();
        ditemukan = true;
      }
    }
  }
  else if (cari == 3)
  {
    int cariUmur;
    cout << "Masukkan umur pasien : ";
    cin >> cariUmur;
    for (int i = 0; i < jumlah; i++)
    {
      if (data[i].umur == cariUmur)
      {
        cout << "\n------Data Pasien ditemukan------\n";
        data[i].tampilkan();
        ditemukan = true;
      }
    }
  }
  else
  {
    cout << "Pilihan tidak valid.\n";
    return;
  }

  if (!ditemukan)
    cout << "Data pasien tidak ditemukan.\n";
}

void Pasien::urutkanPasien(int urut, bool ascending)
{
  Pasien data[100];
  int jumlah = 0;

  ifstream file("pasien.txt");
  string baris;
  while (getline(file, baris) && jumlah < 100)
  {
    stringstream ss(baris);
    string umurStr;

    getline(ss, data[jumlah].nama, ';');
    getline(ss, data[jumlah].idPasien, ';');
    getline(ss, data[jumlah].nik, ';');
    getline(ss, data[jumlah].tempatLahir, ';');
    getline(ss, data[jumlah].tanggalLahir, ';');
    getline(ss, data[jumlah].golDarah, ';');
    getline(ss, data[jumlah].jenisKelamin, ';');
    getline(ss, data[jumlah].alamat, ';');
    getline(ss, data[jumlah].noHP, ';');
    getline(ss, umurStr, ';');
    stringstream(umurStr) >> data[jumlah].umur;

    jumlah++;
  }
  file.close();

  for (int i = 0; i < jumlah - 1; i++)
  {
    for (int j = 0; j < jumlah - 1 - i; j++)
    {

      bool tukar = false;

      if (urut == 1)
      { // ID Pasien
        if ((ascending && data[j].idPasien > data[j + 1].idPasien) ||
            (!ascending && data[j].idPasien < data[j + 1].idPasien))
        {
          tukar = true;
        }
      }
      else if (urut == 2)
      { // Nama Pasien
        if ((ascending && data[j].nama > data[j + 1].nama) ||
            (!ascending && data[j].nama < data[j + 1].nama))
        {
          tukar = true;
        }
      }
      else if (urut == 3)
      { // Umur
        if ((ascending && data[j].umur > data[j + 1].umur) ||
            (!ascending && data[j].umur < data[j + 1].umur))
        {
          tukar = true;
        }
      }
      if (tukar)
      {
        Pasien temp = data[j];
        data[j] = data[j + 1];
        data[j + 1] = temp;
      }
    }
  }

  cout << "\nData setelah diurutkan : \n";
  for (int i = 0; i < jumlah; i++)
  {
    cout << "\nPasien ke-" << i + 1 << ":\n";
    data[i].tampilkan();
  }
}

// MENU ADMIN
class MenuAdmin
{
public:
  void tampilMenu();

private:
  void pendaftaranPasien();
  void sistemLayanan();
  void editPasien();
  void hapusPasien();
  void cariPasien();
  void urutkanPasien();
  void tampilkanDataLayanan();
};

void MenuAdmin::pendaftaranPasien(){
  Pasien p;

  cout << "=== Pendaftaran Pasien Baru ===\n";
  p.idPasien = Pasien::buatIDBaru();
  cout << "ID Pasien (otomatis): " << p.idPasien << endl;
  cout << "Nama                    : ";
  getline(cin, p.nama);
  cout << "NIK                     : ";
  getline(cin, p.nik);
  cout << "Tempat Lahir            : ";
  getline(cin, p.tempatLahir);
  cout << "Tanggal Lahir(DD-MM-DD) : ";
  getline(cin, p.tanggalLahir);
  cout << "No HP                   : ";
  getline(cin, p.noHP);
  cout << "Golongan Darah          : ";
  getline(cin, p.golDarah);
  cout << "Umur                    : ";
  cin >> p.umur;
  cin.ignore();
  cout << "Jenis Kelamin           : ";
  getline(cin, p.jenisKelamin);
  cout << "Alamat                  : ";
  getline(cin, p.alamat);

  p.simpanKeFile();
  cout << "\nPendaftaran berhasil! Data pasien telah disimpan.\n";
}

// DOKTER
class Dokter
{
public:
  string nama;
  string spesialis;

  Dokter() {}
  Dokter(string n, string s) : nama(n), spesialis(s) {}
};

class DaftarDokter
{
private:
  Dokter daftar[20];
  int jumlah;

public:
  DaftarDokter()
  {
    jumlah = 0;
    // IGD
    tambahDokter("dr. Andi", "Sp. EM (Spesialis Emergensi Medik)");
    tambahDokter("dr. Luki", "Sp. EM (Spesialis Emergensi Medik)");
    // Umum
    tambahDokter("dr. Budi", "Dokter Umum");
    tambahDokter("dr. Wati", "Dokter Umum");
    // BPJS (Penyakit Dalam & lainnya)
    tambahDokter("dr. Rina", "Sp. PD (Spesialis Penyakit Dalam)");
    tambahDokter("dr. Diah", "Sp. Paru (Spesialis Paru)");
    tambahDokter("dr. Riko", "Sp. A (Spesialis Anak)");
    // THT, Mata, Kulit
    tambahDokter("dr. Sari", "Sp. THT (Telinga Hidung Tenggorokan)");
    tambahDokter("dr. Lilis", "Sp. M (Spesialis Mata)");
    tambahDokter("dr. Yoga", "Sp. KK (Spesialis Kulit & Kelamin)");
    // Laboratorium (Penanggung Jawab)
    tambahDokter("dr. Farid", "Patologi Klinik");
    // Farmasi (Apoteker)
    tambahDokter("Apt. Nia", "Apoteker");
    tambahDokter("Apt. Yudi", "Apoteker");
  }

  void tambahDokter(string nama, string spesialis)
  {
    if (jumlah < 20)
    {
      daftar[jumlah] = Dokter(nama, spesialis);
      jumlah++;
    }
  }

  void tampilkanDaftar()
  {
    cout << "\n=== DAFTAR DOKTER & SPESIALIS ===\n";
    for (int i = 0; i < jumlah; i++)
    {
      cout << i + 1 << ". " << setw(15) << left << daftar[i].nama << " | " << daftar[i].spesialis << endl;
    }
  }

  Dokter getDokter(int i)
  {
    if (i >= 0 && i < jumlah)
    {
      return daftar[i];
    }
    return Dokter("Tidak Ada", "Tidak Ada");
  }

  int getJumlah() { return jumlah; }
};

// DAFTAR POLI
class Poli
{
public:
  int id;
  string nama;

  Poli() {}
  Poli(int i, string n)
  {
    id = i;
    nama = n;
  }
};

class DaftarPoli
{
private:
  Poli daftar[20];
  int jumlah;

public:
  DaftarPoli()
  {
    jumlah = 0;
    tambahPoli(1, "Poli Anak");
    tambahPoli(2, "Poli Kebidanan & Kandungan");
    tambahPoli(3, "Poli Penyakit Dalam");
    tambahPoli(4, "Poli Bedah");
    tambahPoli(5, "Poli Konsultan Bedah Digestif");
    tambahPoli(6, "Poli Konsultan Bedah Onkologi");
    tambahPoli(7, "Poli Orthopedi");
    tambahPoli(8, "Poli Urologi");
    tambahPoli(9, "Poli Syaraf");
    tambahPoli(10, "Poli Kulit & Kelamin");
    tambahPoli(11, "Poli Mata");
    tambahPoli(12, "Poli Telinga, Hidung & Tenggorokan");
    tambahPoli(13, "Poli Jiwa");
    tambahPoli(14, "Poli Jantung & Pembuluh Darah");
    tambahPoli(15, "Poli Gigi & Mulut");
  }

  int getJumlah() { return jumlah; }

  void tambahPoli(int id, string nama)
  {
    if (jumlah < 20)
    {
      daftar[jumlah] = Poli(id, nama);
      jumlah++;
    }
  }

  void tampilkanDaftar()
  {
    cout << "===========================================\n";
    cout << "                 DAFTAR POLI              \n";
    cout << "===========================================\n";
    for (int i = 0; i < jumlah; i++)
    {
      cout << setw(2) << daftar[i].id << ". " << daftar[i].nama << endl;
    }
    cout << "===========================================\n";
  }

  Poli getPoli(int id)
  {
    for (int i = 0; i < jumlah; i++)
    {
      if (daftar[i].id == id)
      {
        return daftar[i];
      }
    }
    return Poli(0, "Poli Tidak Ditemukan");
  }
};

// RAWAT INAP
class Rawatinap
{
private:
  int biayaRawatInap;
  const int biayaAdmin = 20000;
  int jumlahBayar;
  int jumlahHari;
  string kelas, ruangan;

  string ruangVIP[3] = {"Mawar 01", "Mawar 02", "Mawar 03"};
  string ruang1[3] = {"Sakura 01", "Sakura 02", "Sakura 03"};
  string ruang2[3] = {"Melati 01", "Melati 02", "Melati 03"};
  string ruang3[3] = {"Kamboja 01", "Kamboja 02", "Kamboja 03"};

public:
  void pilihKelas();
  void rincian();
  void struk();
  void setJumlahBayar(int bayar) { jumlahBayar = bayar; }
  void setJumlahHari(int hari) { jumlahHari = hari; }
  string pilihRuangan(string ruanganList[]);
};

string Rawatinap::pilihRuangan(string ruanganList[])
{
  cout << "Pilih ruangan:\n";
  for (int i = 0; i < 3; ++i)
  {
    cout << i + 1 << ". " << ruanganList[i] << endl;
  }
  int pilihan;
  cout << "Masukkan pilihan (1-3): ";
  cin >> pilihan;
  if (pilihan >= 1 && pilihan <= 3)
  {
    return ruanganList[pilihan - 1];
  }
  else
  {
    cout << "Pilihan tidak valid. Gunakan ruangan default.\n";
    return ruanganList[0];
  }
}

void Rawatinap::pilihKelas()
{
  cout << "------------------------------------\n";
  cout << "      Pilih Kelas Rawat Inap        \n";
  cout << "------------------------------------\n";
  cout << "1. VIP     - Rp 200.000/hari\n";
  cout << "2. Kelas 1 - Rp 150.000/hari\n";
  cout << "3. Kelas 2 - Rp 100.000/hari\n";
  cout << "4. Kelas 3 - Rp  50.000/hari\n";
  cout << "------------------------------------\n";
  cout << "Masukkan pilihan: ";
  int pilih;
  cin >> pilih;

  switch (pilih)
  {
  case 1:
    kelas = "VIP";
    biayaRawatInap = 200000;
    ruangan = pilihRuangan(ruangVIP);
    break;
  case 2:
    kelas = "Kelas 1";
    biayaRawatInap = 150000;
    ruangan = pilihRuangan(ruang1);
    break;
  case 3:
    kelas = "Kelas 2";
    biayaRawatInap = 100000;
    ruangan = pilihRuangan(ruang2);
    break;
  case 4:
    kelas = "Kelas 3";
    biayaRawatInap = 50000;
    ruangan = pilihRuangan(ruang3);
    break;
  default:
    cout << "Pilihan tidak valid. Ditetapkan ke Kelas 3 secara default.\n";
    kelas = "Kelas 3";
    biayaRawatInap = 50000;
    ruangan = pilihRuangan(ruang3);
  }

  cout << "Jumlah hari inap: ";
  cin >> jumlahHari;
}

void Rawatinap::rincian()
{
  int total = (biayaRawatInap * jumlahHari) + biayaAdmin;

  cout << "Total Biaya: Rp " << total << "\nMasukkan pembayaran: Rp ";
  int bayar;
  cin >> bayar;
  setJumlahBayar(bayar);

  int kembalian = bayar - total;

  cout << "\n===========================================\n";
  cout << "              RINCIAN RAWAT INAP           \n";
  cout << "===========================================\n";
  cout << "Kelas        : " << kelas << endl;
  cout << "Ruangan      : " << ruangan << endl;
  cout << "Hari Inap    : " << jumlahHari << endl;
  cout << "Biaya Inap   : Rp " << biayaRawatInap * jumlahHari << endl;
  cout << "Biaya Admin  : Rp " << biayaAdmin << endl;
  cout << "Total        : Rp " << total << endl;
  cout << "Dibayar      : Rp " << bayar << endl;
  cout << "Kembalian    : Rp " << kembalian << endl;
}

void Rawatinap::struk()
{
  time_t now = time(0);
  tm *ltm = localtime(&now);

  int total = (biayaRawatInap * jumlahHari) + biayaAdmin;
  int kembalian = jumlahBayar - total;

  cout << "\n========== STRUK PEMBAYARAN ==========\n";
  cout << "Tanggal       : " << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << endl;
  cout << "Waktu         : " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl;
  cout << "Kelas         : " << kelas << endl;
  cout << "Ruangan       : " << ruangan << endl;
  cout << "Jumlah Hari   : " << jumlahHari << endl;
  cout << "Biaya Rawat   : Rp " << biayaRawatInap * jumlahHari << endl;
  cout << "Biaya Admin   : Rp " << biayaAdmin << endl;
  cout << "Total Bayar   : Rp " << total << endl;
  cout << "Dibayar       : Rp " << jumlahBayar << endl;
  cout << "Kembalian     : Rp " << kembalian << endl;
  cout << "======================================\n";
}

// ==== Class Rawat Jalan ====
class Rawatjalan
{
private:
  int biayaRawatJalan;
  const int biayaAdmin = 15000;
  int jumlahBayar;
  int jumlahHari;
  string kelasJalan, ruanganJalan;

public:
  void pilihKelas();
  void prosesPembayaran();
  void rincian();
  void struk();
  void setJumlahBayar(int bayar) { jumlahBayar = bayar; }
  void setJumlahHari(int hari) { jumlahHari = hari; }
};

void Rawatjalan::pilihKelas()
{
  cout << "\n======= PILIH KELAS RAWAT JALAN =======\n";
  cout << "1. VIP     - Rp 100.000/hari (Flamboyan RJ01)\n";
  cout << "2. Kelas 1 - Rp  75.000/hari (Dahlia RJ02)\n";
  cout << "3. Kelas 2 - Rp  50.000/hari (Teratai RJ03)\n";
  cout << "4. Kelas 3 - Rp  30.000/hari (Soka RJ04)\n";
  cout << "Masukkan pilihan: ";
  int pilih;
  cin >> pilih;

  switch (pilih)
  {
  case 1:
    kelasJalan = "VIP";
    ruanganJalan = "Flamboyan RJ01";
    biayaRawatJalan = 100000;
    break;
  case 2:
    kelasJalan = "Kelas 1";
    ruanganJalan = "Dahlia RJ02";
    biayaRawatJalan = 75000;
    break;
  case 3:
    kelasJalan = "Kelas 2";
    ruanganJalan = "Teratai RJ03";
    biayaRawatJalan = 50000;
    break;
  case 4:
    kelasJalan = "Kelas 3";
    ruanganJalan = "Soka RJ04";
    biayaRawatJalan = 30000;
    break;
  default:
    cout << "Pilihan tidak valid.\n";
    return;
  }

  cout << "Jumlah hari rawat jalan: ";
  cin >> jumlahHari;
}

void Rawatjalan::rincian()
{
  int total = (biayaRawatJalan * jumlahHari) + biayaAdmin;

  cout << "Total Biaya: Rp " << total << "\nMasukkan pembayaran: Rp ";
  int bayar;
  cin >> bayar;

  setJumlahBayar(bayar);

  int kembalian = bayar - total;

  cout << "\n===========================================\n";
  cout << "              RINCIAN RAWAT JALAN          \n";
  cout << "===========================================\n";
  cout << "Kelas        : " << kelasJalan << endl;
  cout << "Ruangan      : " << ruanganJalan << endl;
  cout << "Hari Rawat   : " << jumlahHari << endl;
  cout << "Biaya Rawat  : Rp " << biayaRawatJalan * jumlahHari << endl;
  cout << "Biaya Admin  : Rp " << biayaAdmin << endl;
  cout << "Total Bayar  : Rp " << total << endl;
  cout << "Dibayar      : Rp " << bayar << endl;
  cout << "Kembalian    : Rp " << kembalian << endl;
}

void Rawatjalan::struk()
{
  time_t now = time(0);
  tm *ltm = localtime(&now);

  int total = (biayaRawatJalan * jumlahHari) + biayaAdmin;
  int kembalian = jumlahBayar - total;

  cout << "\n========== STRUK PEMBAYARAN ==========\n";
  cout << "Tanggal     : " << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << endl;
  cout << "Waktu       : " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl;
  cout << "Kelas       : " << kelasJalan << endl;
  cout << "Ruangan     : " << ruanganJalan << endl;
  cout << "Jumlah Hari : " << jumlahHari << endl;
  cout << "Biaya Rawat   : Rp " << biayaRawatJalan * jumlahHari << endl;
  cout << "Biaya Admin   : Rp " << biayaAdmin << endl;
  cout << "Total Bayar   : Rp " << total << endl;
  cout << "Dibayar       : Rp " << jumlahBayar << endl;
  cout << "Kembalian     : Rp " << kembalian << endl;
  cout << "======================================\n";
}

bool sudahDaftar(const string &idPasien, string &layananSebelumnya)
{
  ifstream file("pelayanan.txt");
  string baris;
  while (getline(file, baris))
  {
    stringstream ss(baris);
    string id, nama, layanan;
    getline(ss, id, ';');
    getline(ss, nama, ';');
    getline(ss, layanan, ';');
    if (id == idPasien)
    {
      layananSebelumnya = layanan;
      return true;
    }
  }
  return false;
}

void simpanLogPelayanan(const string &idPasien, const string &namaPasien, const string &layanan)
{
  ofstream file("pelayanan.txt", ios::app);
  if (file.is_open())
  {
    file << idPasien << ";" << namaPasien << ";" << layanan << "\n";
    file.close();
  }
}

// IGD
class SistemIGD
{
public:
  void pendaftaranIGD();
  void tampilkanDataIGD();
  void cariDataPasienIGD();
  void bubbleSortByidPasien();
  void bubbleSortByNama();
  void menu();

private:
  void layaniPasienIGD(const Pasien &p);
};

void SistemIGD::pendaftaranIGD()
{
  string id;
  cout << "\n===== LAYANAN IGD =====\n";
  cout << "Masukkan ID Pasien: ";
  getline(cin, id);

  ifstream file("pasien.txt");
  string baris;
  bool ditemukan = false;
  Pasien p;

  while (getline(file, baris))
  {
    stringstream ss(baris);
    string umurStr;

    getline(ss, p.nama, ';');
    getline(ss, p.idPasien, ';');
    getline(ss, p.nik, ';');
    getline(ss, p.tempatLahir, ';');
    getline(ss, p.tanggalLahir, ';');
    getline(ss, p.noHP, ';');
    getline(ss, p.golDarah, ';');
    getline(ss, umurStr, ';');
    stringstream(umurStr) >> p.umur;
    getline(ss, p.jenisKelamin, ';');
    getline(ss, p.alamat, ';');

    if (p.idPasien == id)
    {
      ditemukan = true;
      break;
    }
  }
  file.close();

  if (ditemukan)
  {
    string layananSebelumnya;
    if (sudahDaftar(p.idPasien, layananSebelumnya))
    {
      cout << "\nPasien sudah terdaftar di layanan: " << layananSebelumnya << ". Tidak bisa mendaftar dua kali.\n";
      return;
    }
    cout << "\nData pasien ditemukan. Melanjutkan ke layanan IGD...\n";
    layaniPasienIGD(p);
    simpanLogPelayanan(p.idPasien, p.nama, "IGD");
  }
  else
  {
    cout << "ID Pasien tidak ditemukan. Kembali ke menu utama.\n";
  }
}

void SistemIGD::layaniPasienIGD(const Pasien &p)
{
  cout << "\n=== LAYANAN IGD ===\n";
  cout << "Nama Pasien : " << p.nama << endl;
  cout << "ID Pasien   : " << p.idPasien << endl;

  string keluhan;
  cout << "Masukkan keluhan pasien : ";
  getline(cin, keluhan);

  int pilihKedaruratan;
  string tingkatKedaruratan;
  bool inputValid = false;

  do
  {
    cout << "\n===========================================\n";
    cout << "Pilih Tingkat Kedaruratan:\n";
    cout << "1. Ringan\n";
    cout << "2. Sedang\n";
    cout << "3. Berat\n";
    cout << "Masukkan pilihan (1-3) : ";
    cin >> pilihKedaruratan;
    cin.ignore();

    switch (pilihKedaruratan)
    {
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

  DaftarDokter daftar;
  daftar.tampilkanDaftar();

  int pilih;
  do
  {
    cout << "Pilih dokter berdasarkan nomor (1 - " << daftar.getJumlah() << "): ";
    cin >> pilih;
    cin.ignore();
    if (pilih < 1 || pilih > daftar.getJumlah())
    {
      cout << "Pilihan tidak valid. Coba lagi.\n";
    }
  } while (pilih < 1 || pilih > daftar.getJumlah());

  Dokter d = daftar.getDokter(pilih - 1);
  cout << "\nPasien akan ditangani oleh : " << d.nama << " - " << d.spesialis << endl;

  cout << "\nPasien sedang dalam penanganan...\n";
  cout << "-----------------------------------\n";
  cout << "Selesai melayani pasien.\n";

  // Ambil waktu saat ini
  time_t now = time(0);
  string waktu = ctime(&now);
  waktu.pop_back();

  // Simpan ke file igd.txt
  ofstream file("igd.txt", ios::app);
  if (file.is_open())
  {
    file << waktu << ";" << p.idPasien << ";" << p.nama << ";" << keluhan << ";"
         << tingkatKedaruratan << ";" << d.nama << ";" << d.spesialis << ";\n";
    file.close();
  }
  else
  {
    cout << "Gagal menyimpan data layanan IGD!\n";
  }
}

void SistemIGD::tampilkanDataIGD()
{
  ifstream file("igd.txt");
  if (!file.is_open())
  {
    cout << "Belum ada data layanan IGD.\n";
    return;
  }

  string baris;
  int i = 1;

  cout << "\n==== DAFTAR DATA LAYANAN PASIEN IGD ====\n";
  while (getline(file, baris))
  {
    stringstream ss(baris);
    string waktu, idPasien, namaPasien, keluhan, tingkatKedaruratan, namaDokter,
        spesialis;

    getline(ss, waktu, ';');
    getline(ss, idPasien, ';');
    getline(ss, namaPasien, ';');
    getline(ss, keluhan, ';');
    getline(ss, tingkatKedaruratan, ';');
    getline(ss, namaDokter, ';');
    getline(ss, spesialis, ';');

    cout << "Pasien #" << i++ << endl;
    cout << "Waktu Layanan       : " << waktu << endl;
    cout << "ID Pasien           : " << idPasien << endl;
    cout << "Nama Pasien         : " << namaPasien << endl;
    cout << "Keluhan             : " << keluhan << endl;
    cout << "Tingkat Kedaruratan : " << tingkatKedaruratan << endl;
    cout << "Dokter Penanganan   : " << namaDokter << endl;
    cout << "Spesialis           : " << spesialis << endl;
    cout << "----------------------------------------\n";
  }

  file.close();
}

void SistemIGD::bubbleSortByidPasien()
{
  ifstream file("igd.txt");
  vector<string> data;

  string baris;
  while (getline(file, baris))
  {
    data.push_back(baris);
  }
  file.close();

  int n = data.size();
  for (int i = 0; i < n - 1; ++i)
  {
    for (int j = 0; j < n - i - 1; ++j)
    {
      stringstream ss1(data[j]), ss2(data[j + 1]);
      string waktu1, id1;
      string waktu2, id2;

      getline(ss1, waktu1, ';');
      getline(ss1, id1, ';');
      getline(ss2, waktu2, ';');
      getline(ss2, id2, ';');

      if (id1 > id2)
      {
        string temp = data[j];
        data[j] = data[j + 1];
        data[j + 1] = temp;
      }
    }
  }

  cout << "\n=== DATA PASIEN IGD BERDASARKAN ID ===\n";
  for (int i = 0; i < n; ++i)
  {
    stringstream ss(data[i]);
    string waktu, idPasien, namaPasien, keluhan, kedaruratan, namaDokter, spesialis;

    getline(ss, waktu, ';');
    getline(ss, idPasien, ';');
    getline(ss, namaPasien, ';');
    getline(ss, keluhan, ';');
    getline(ss, kedaruratan, ';');
    getline(ss, namaDokter, ';');
    getline(ss, spesialis, ';');

    cout << "Waktu Layanan       : " << waktu << endl;
    cout << "ID Pasien           : " << idPasien << endl;
    cout << "Nama Pasien         : " << namaPasien << endl;
    cout << "Keluhan             : " << keluhan << endl;
    cout << "Tingkat Kedaruratan : " << kedaruratan << endl;
    cout << "Dokter Penanganan   : " << namaDokter << endl;
    cout << "Spesialis           : " << spesialis << endl;
    cout << "----------------------------------------\n";
  }
}
void SistemIGD::bubbleSortByNama()
{
  ifstream file("igd.txt");
  vector<string> data;

  string baris;
  while (getline(file, baris))
  {
    data.push_back(baris);
  }
  file.close();

  int n = data.size();
  for (int i = 0; i < n - 1; ++i)
  {
    for (int j = 0; j < n - i - 1; ++j)
    {
      stringstream ss1(data[j]), ss2(data[j + 1]);
      string waktu1, id1, nama1;
      string waktu2, id2, nama2;

      getline(ss1, waktu1, ';');
      getline(ss1, id1, ';');
      getline(ss1, nama1, ';');
      getline(ss2, waktu2, ';');
      getline(ss2, id2, ';');
      getline(ss2, nama2, ';');

      if (nama1 > nama2)
      {
        string temp = data[j];
        data[j] = data[j + 1];
        data[j + 1] = temp;
      }
    }
  }

  cout << "\n=== DATA PASIEN IGD BERDASARKAN NAMA ===\n";
  for (int i = 0; i < n; ++i)
  {
    stringstream ss(data[i]);
    string waktu, idPasien, namaPasien, keluhan, kedaruratan, namaDokter, spesialis;

    getline(ss, waktu, ';');
    getline(ss, idPasien, ';');
    getline(ss, namaPasien, ';');
    getline(ss, keluhan, ';');
    getline(ss, kedaruratan, ';');
    getline(ss, namaDokter, ';');
    getline(ss, spesialis, ';');

    cout << "Waktu Layanan       : " << waktu << endl;
    cout << "ID Pasien           : " << idPasien << endl;
    cout << "Nama Pasien         : " << namaPasien << endl;
    cout << "Keluhan             : " << keluhan << endl;
    cout << "Tingkat Kedaruratan : " << kedaruratan << endl;
    cout << "Dokter Penanganan   : " << namaDokter << endl;
    cout << "Spesialis           : " << spesialis << endl;
    cout << "----------------------------------------\n";
  }
}

void SistemIGD::cariDataPasienIGD()
{
  ifstream file("igd.txt");
  if (!file.is_open())
  {
    cout << "\nBelum ada data layanan IGD yang tersimpan.\n";
    return;
  }

  int pilihan;
  string keyword;
  bool ditemukan = false;

  cout << "\n=== CARI DATA LAYANAN PASIEN IGD ===\n";
  cout << "Cari berdasarkan:\n";
  cout << "1. ID Pasien\n";
  cout << "2. Nama Pasien\n";
  cout << "3. Tingkat Kedaruratan\n";
  cout << "Masukkan pilihan (1-3): ";
  cin >> pilihan;
  cin.ignore();

  switch (pilihan)
  {
  case 1:
    cout << "Masukkan ID Pasien (contoh: RM0001): ";
    break;
  case 2:
    cout << "Masukkan Nama Pasien: ";
    break;
  case 3:
    cout << "Masukkan Tingkat Kedaruratan (Ringan/Sedang/Berat): ";
    break;
  default:
    cout << "Pilihan tidak valid.\n";
    return;
  }
  getline(cin, keyword);

  string baris;
  int i = 1;

  cout << "\nHasil pencarian:\n";
  while (getline(file, baris))
  {
    stringstream ss(baris);
    string waktu, idPasien, namaPasien, keluhan, kedaruratan, namaDokter, spesialis;

    getline(ss, waktu, ';');
    getline(ss, idPasien, ';');
    getline(ss, namaPasien, ';');
    getline(ss, keluhan, ';');
    getline(ss, kedaruratan, ';');
    getline(ss, namaDokter, ';');
    getline(ss, spesialis, ';');

    bool cocok = false;
    switch (pilihan)
    {
    case 1:
      cocok = (idPasien == keyword);
      break;
    case 2:
      cocok = (namaPasien.find(keyword) != string::npos);
      break;
    case 3:
      cocok = (kedaruratan == keyword);
      break;
    }

    if (cocok)
    {
      ditemukan = true;
      cout << "\n-----Data Pasien ke- " << i++ << "-----\n";
      cout << "Waktu Layanan       : " << waktu << endl;
      cout << "ID Pasien           : " << idPasien << endl;
      cout << "Nama Pasien         : " << namaPasien << endl;
      cout << "Keluhan             : " << keluhan << endl;
      cout << "Tingkat Kedaruratan : " << kedaruratan << endl;
      cout << "Dokter Penanganan   : " << namaDokter << endl;
      cout << "Spesialis           : " << spesialis << endl;
      cout << "----------------------------------------\n";
    }
  }

  if (!ditemukan)
  {
    cout << "\nData tidak ditemukan.\n";
  }

  file.close();
}

void SistemIGD::menu(){
  int pilihan;

  do  {
    cout << "\n===========================================\n";
    cout << "             Sistem Manajemen IGD          \n";
    cout << "===========================================\n";
    cout << "1. Pendaftaran Pasien IGD\n";
    cout << "2. Tampilkan Data Semua Pasien\n";
    cout << "3. Sorting Data Pasien\n";
    cout << "4. Pencarian Data Pasien\n";
    cout << "5. Keluar\n";
    cout << "=============================================\n";
    cout << "Pilih menu (1-5): ";
    cin >> pilihan;

    switch (pilihan)    {
    case 1:
      cin.ignore();
      pendaftaranIGD();
      break;
    case 2:
      tampilkanDataIGD();
      break;
    case 4:
      cariDataPasienIGD();
      break;
    case 3:{
      int pilih;
      cout << "\n===========================================\n";
      cout << "           MENU SORTING DATA PASIEN               \n";
      cout << "=============================================\n";
      cout << "Urutkan Data Pasien berdasarkan : \n";
      cout << "1. ID Pasien\n";
      cout << "2. Nama\n";
      cout << "Masukkan Pilihan : ";
      cin >> pilih;

      if (pilih == 1)
        bubbleSortByidPasien();
      else if (pilih == 2)
        bubbleSortByNama();
      else
        cout << "Pilihan tidak valid.\n";
      break;
    }
    case 5:
      cout << "\nTerima kasih telah menggunkan Sistem IGD\n";
      cout << "Program selesai.\n";
      break;
    default:
      cout << "\nPilihan tidak valid. Coba lagi.\n";
    }

  } while (pilihan != 5);
}

// SISTEM LAYANAN UMUM
class SistemUmum {
private:
  void layaniPasienUmum(const Pasien &p);
  Rawatinap rawatInap;
  Rawatjalan rawatJalan;
  int jenisRawatDipilih;

public:
  void PendaftaranUmum();
  void pilihRawat();
  void prosesPembayaran();
  void cetakStruk();
  void tampilkanDataUmum();
  void cariData();
  void urutkanData();
  void menu();
};

void SistemUmum::PendaftaranUmum()
{
  string id;
  cout << "\n===== LAYANAN UMUM =====\n";
  cout << "Masukkan ID Pasien: ";
  getline(cin, id);

  ifstream file("pasien.txt");
  string baris;
  bool ditemukan = false;
  Pasien p;

  while (getline(file, baris))
  {
    stringstream ss(baris);
    string umurStr;

    getline(ss, p.nama, ';');
    getline(ss, p.idPasien, ';');
    getline(ss, p.nik, ';');
    getline(ss, p.tempatLahir, ';');
    getline(ss, p.tanggalLahir, ';');
    getline(ss, p.noHP, ';');
    getline(ss, p.golDarah, ';');
    getline(ss, umurStr, ';');
    stringstream(umurStr) >> p.umur;
    getline(ss, p.jenisKelamin, ';');
    getline(ss, p.alamat, ';');

    if (p.idPasien == id)
    {
      ditemukan = true;
      break;
    }
  }
  file.close();

  if (ditemukan)
  {
    string layananSebelumnya;
    if (sudahDaftar(p.idPasien, layananSebelumnya))
    {
      cout << "\nPasien sudah terdaftar di layanan : " << layananSebelumnya << ". Tidak bisa mendaftar dua kali.\n";
      return;
    }
    cout << "\nData pasien ditemukan. Melanjutkan ke layanan Umum...\n";
    layaniPasienUmum(p);
    simpanLogPelayanan(p.idPasien, p.nama, "Umum");
  }
  else
  {
    cout << "\nID Pasien tidak ditemukan. Kembali ke menu.\n";
  }
}

void SistemUmum::layaniPasienUmum(const Pasien &p)
{
  cout << "\n=== LAYANAN UMUM ===\n";
  cout << "Nama Pasien : " << p.nama << endl;
  cout << "ID Pasien   : " << p.idPasien << endl;

  string keluhan;
  cout << "\nMasukkan keluhan pasien : ";
  getline(cin, keluhan);

  DaftarPoli daftarPoli;
  daftarPoli.tampilkanDaftar();

  int pilih;
  cout << "Pilih poli berdasarkan nomor (1 - " << daftarPoli.getJumlah() << "): ";
  cin >> pilih;
  cin.ignore();

  Poli poliDipilih = daftarPoli.getPoli(pilih);

  cout << "Pasien akan dirujuk ke : " << poliDipilih.nama << endl;
  cout << "\nPasien sedang dalam proses layanan Umum...\n";
  cout << "-------------------------------------------\n";
  cout << "Selesai melayani pasien di Umum.\n";

  // Simpan data
  time_t now = time(0);
  string waktu = ctime(&now);
  waktu.pop_back();

  ofstream file("umum.txt", ios::app);
  if (file.is_open())
  {
    file << waktu << ";" << p.idPasien << ";" << p.nama << ";" << keluhan
         << ";" << poliDipilih.nama << ";\n";
    file.close();
  }
  else
  {
    cout << "Gagal menyimpan data layanan Umum!\n";
  }
}

void SistemUmum::pilihRawat()
{
  cout << "\n===== PILIH JENIS RAWAT =====\n";
  cout << "1. Rawat Inap\n";
  cout << "2. Rawat Jalan\n";
  cout << "Masukkan pilihan: ";
  cin >> jenisRawatDipilih;
  cin.ignore();

  if (jenisRawatDipilih == 1)
  {
    cout << "\nJenis Rawat dipilih: Rawat Inap\n";
    cout << "\n------------------------------------\n";
    cout << "        Daftar Kelas Rawat Inap     \n";
    cout << "------------------------------------\n";
    cout << "1. VIP     - Rp 200.000/hari\n";
    cout << "2. Kelas 1 - Rp 150.000/hari\n";
    cout << "3. Kelas 2 - Rp 100.000/hari\n";
    cout << "4. Kelas 3 - Rp  50.000/hari\n";
    cout << "------------------------------------\n\n";
    rawatInap.pilihKelas();
  }
  else if (jenisRawatDipilih == 2)
  {
    cout << "\nJenis Rawat dipilih: Rawat Jalan\n\n";
    rawatJalan.pilihKelas();
  }
  else
  {
    cout << "\nPilihan tidak valid. Jenis rawat belum dipilih.\n\n";
  }
}

void SistemUmum::prosesPembayaran()
{
  if (jenisRawatDipilih == 1)
  {
    rawatInap.rincian(); // Langsung proses pembayaran dan tampilkan rincian
  }
  else if (jenisRawatDipilih == 2)
  {
    rawatJalan.rincian(); // Langsung proses pembayaran dan tampilkan rincian
  }
  else
  {
    cout << "Silakan pilih jenis rawat terlebih dahulu (menu 2).\n";
  }
}

void SistemUmum::cetakStruk()
{
  if (jenisRawatDipilih == 1)
  {
    rawatInap.struk();
  }
  else if (jenisRawatDipilih == 2)
  {
    rawatJalan.struk();
  }
  else
  {
    cout << "Silakan pilih jenis rawat dan lakukan pembayaran terlebih dahulu.\n";
  }
}

void SistemUmum::tampilkanDataUmum()
{
  ifstream file("umum.txt");
  if (!file.is_open())
  {
    cout << "Belum ada data layanan Umum.\n";
    return;
  }

  string baris;
  int i = 1;

  cout << "\n==== DAFTAR DATA LAYANAN UMUM ====\n";
  while (getline(file, baris))
  {
    stringstream ss(baris);
    string waktu, id, nama, keluhan, poli;
    getline(ss, waktu, ';');
    getline(ss, id, ';');
    getline(ss, nama, ';');
    getline(ss, keluhan, ';');
    getline(ss, poli, ';');

    cout << "\nData ke-" << i++ << ":\n";
    cout << "Waktu     : " << waktu << "\n";
    cout << "ID Pasien : " << id << "\n";
    cout << "Nama      : " << nama << "\n";
    cout << "Keluhan   : " << keluhan << "\n";
    cout << "Poli      : " << poli << "\n";
  }

  file.close();
}

void SistemUmum::cariData()
{
  string cariID;
  cout << "Masukkan ID Pasien yang dicari: ";
  getline(cin, cariID);

  ifstream file("umum.txt");
  string baris;
  bool ditemukan = false;

  while (getline(file, baris))
  {
    stringstream ss(baris);
    string waktu, id, nama, keluhan, poli;
    getline(ss, waktu, ';');
    getline(ss, id, ';');
    getline(ss, nama, ';');
    getline(ss, keluhan, ';');
    getline(ss, poli, ';');

    if (id == cariID)
    {
      cout << "\n==== Data Ditemukan ====\n";
      cout << "Waktu     : " << waktu << "\n";
      cout << "ID Pasien : " << id << "\n";
      cout << "Nama      : " << nama << "\n";
      cout << "Keluhan   : " << keluhan << "\n";
      cout << "Poli      : " << poli << "\n";
      ditemukan = true;
      break;
    }
  }

  if (!ditemukan)
  {
    cout << "Data tidak ditemukan.\n";
  }

  file.close();
}

void SistemUmum::urutkanData()
{
  ifstream file("umum.txt");
  string data[100];
  int jumlahData = 0;
  string baris;

  while (getline(file, baris) && jumlahData < 100)
  {
    data[jumlahData++] = baris;
  }
  file.close();

  for (int i = 0; i < jumlahData - 1; i++)
  {
    for (int j = 0; j < jumlahData - i - 1; j++)
    {
      stringstream ss1(data[j]), ss2(data[j + 1]);
      string waktu1, id1, dummy1, dummy2, dummy3;
      string waktu2, id2, dummy4, dummy5, dummy6;

      getline(ss1, waktu1, ';');
      getline(ss1, id1, ';');
      getline(ss2, waktu2, ';');
      getline(ss2, id2, ';');

      if (id1 > id2)
      {
        swap(data[j], data[j + 1]);
      }
    }
  }

  cout << "\n==== DATA UMUM SETELAH DIURUTKAN BERDASARKAN ID PASIEN ====\n";
  for (int i = 0; i < jumlahData; i++)
  {
    stringstream ss(data[i]);
    string waktu, id, nama, keluhan, poli;

    getline(ss, waktu, ';');
    getline(ss, id, ';');
    getline(ss, nama, ';');
    getline(ss, keluhan, ';');
    getline(ss, poli, ';');

    cout << "\nData ke-" << (i + 1) << ":\n";
    cout << "Waktu     : " << waktu << "\n";
    cout << "ID Pasien : " << id << "\n";
    cout << "Nama      : " << nama << "\n";
    cout << "Keluhan   : " << keluhan << "\n";
    cout << "Poli      : " << poli << "\n";
  }
}

void SistemUmum::menu()
{
  int pilihan;
  do
  {
    cout << "\n===== MENU LAYANAN UMUM =====\n";
    cout << "1. Pendaftaran Pasien Umum\n";
    cout << "2. Pilih Jenis Rawat (Inap / Jalan)\n";
    cout << "3. Proses Pembayaran Layanan\n";
    cout << "4. Cetak Struk Pembayaran\n";
    cout << "5. Tampilkan Semua Data Pasien Umum\n";
    cout << "6. Cari Data Pasien\n";
    cout << "7. Urutkan Data Pasien\n";
    cout << "8. Kembali ke Menu Utama\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    cin.ignore();

    switch (pilihan)
    {
    case 1:
      cin.ignore();
      PendaftaranUmum();
      break;
    case 2:
      pilihRawat();
      break;
    case 3:
      prosesPembayaran();
      break;
    case 4:
      cetakStruk();
      break;
    case 5:
      tampilkanDataUmum();
      break;
    case 6:
      cariData();
      break;
    case 7:
      urutkanData();
      break;
    case 8:
      cout << "Kembali ke menu utama.\n";
      break;
    default:
      cout << "Pilihan tidak valid.\n";
    }
  } while (pilihan != 8);
}

// SISTEM LAYANAN BPJS
class SistemBPJS
{
public:
  void PendaftaranBPJS();
  void pilihRawat();
  void pilihKelas();
  void cetakStruk();
  void prosesPembayaran();
  void tampilkanDataBPJS();
  void cariData();
  void urutkanData();
  void menu();

private:
  void layaniPasienBPJS(const Pasien &p);
  Rawatinap rawatInap;
  Rawatjalan rawatJalan;
  int jenisRawatDipilih;
};

void SistemBPJS::PendaftaranBPJS()
{
  string id;
  cout << "\n===== LAYANAN BPJS =====\n";
  cout << "Masukkan ID Pasien: ";
  getline(cin, id);

  ifstream file("pasien.txt");
  string baris;
  bool ditemukan = false;
  Pasien p;

  while (getline(file, baris))
  {
    stringstream ss(baris);
    string umurStr;

    getline(ss, p.nama, ';');
    getline(ss, p.idPasien, ';');
    getline(ss, p.nik, ';');
    getline(ss, p.tempatLahir, ';');
    getline(ss, p.tanggalLahir, ';');
    getline(ss, p.noHP, ';');
    getline(ss, p.golDarah, ';');
    getline(ss, umurStr, ';');
    stringstream(umurStr) >> p.umur;
    getline(ss, p.jenisKelamin, ';');
    getline(ss, p.alamat, ';');

    if (p.idPasien == id)
    {
      ditemukan = true;
      break;
    }
  }
  file.close();

  if (ditemukan)
  {
    string layananSebelumnya;
    if (sudahDaftar(p.idPasien, layananSebelumnya))
    {
      cout << "\nPasien sudah terdaftar di layanan : " << layananSebelumnya << ". Tidak bisa mendaftar dua kali.\n";
      return;
    }
    cout << "\nData pasien ditemukan. Melanjutkan ke layanan BPJS...\n";
    layaniPasienBPJS(p);
    simpanLogPelayanan(p.idPasien, p.nama, "BPJS");
  }
  else
  {
    cout << "\nID Pasien tidak ditemukan. Kembali ke menu.\n";
  }
}

void SistemBPJS::layaniPasienBPJS(const Pasien &p)
{
  cout << "\n=== LAYANAN BPJS ===\n";
  cout << "Nama Pasien : " << p.nama << endl;
  cout << "ID Pasien   : " << p.idPasien << endl;

  string keluhan;
  cout << "\nMasukkan keluhan pasien : ";
  getline(cin, keluhan);

  DaftarPoli daftarPoli;
  daftarPoli.tampilkanDaftar();

  int pilih;
  cout << "Pilih poli berdasarkan nomor (1 - " << daftarPoli.getJumlah() << "): ";
  cin >> pilih;
  cin.ignore();

  Poli poliDipilih = daftarPoli.getPoli(pilih);

  cout << "Pasien akan dirujuk ke : " << poliDipilih.nama << endl;
  cout << "\nPasien sedang dalam proses layanan BPJS...\n";
  cout << "-------------------------------------------\n";
  cout << "Selesai melayani pasien di BPJS.\n";

  // Ambil waktu saat ini
  time_t now = time(0);
  string waktu = ctime(&now);
  waktu.pop_back();

  ofstream file("bpjs.txt", ios::app);
  if (file.is_open())
  {
    file << waktu << ";" << p.idPasien << ";" << p.nama << ";" << keluhan
         << ";" << poliDipilih.nama << ";\n";
    file.close();
  }
  else
  {
    cout << "Gagal menyimpan data layanan BPJS!\n";
  }
}

void SistemBPJS::pilihRawat()
{
  cout << "\n===== PILIH JENIS RAWAT =====\n";
  cout << "1. Rawat Inap\n";
  cout << "2. Rawat Jalan\n";
  cout << "Masukkan pilihan: ";
  cin >> jenisRawatDipilih;
  cin.ignore();

  if (jenisRawatDipilih == 1)
  {
    cout << "\nJenis Rawat dipilih: Rawat Inap\n";
    cout << "------------------------------------\n";
    cout << "      Pilih Kelas Rawat Inap        \n";
    cout << "------------------------------------\n";
    cout << "1. VIP     - Rp 200.000/hari\n";
    cout << "2. Kelas 1 - Rp 150.000/hari\n";
    cout << "3. Kelas 2 - Rp 100.000/hari\n";
    cout << "4. Kelas 3 - Rp  50.000/hari\n";
    cout << "------------------------------------\n";
    rawatJalan.pilihKelas();
  }
  else if (jenisRawatDipilih == 2)
  {
    cout << "\nJenis Rawat dipilih: Rawat Jalan\n";
    rawatJalan.pilihKelas();
  }
  else
  {
    cout << "\nPilihan tidak valid. Jenis rawat belum dipilih.\n";
  }
}

void SistemBPJS::prosesPembayaran()
{
  if (jenisRawatDipilih == 1)
  {
    rawatInap.rincian(); // Langsung tampilkan rincian & input pembayaran
  }
  else if (jenisRawatDipilih == 2)
  {
    rawatJalan.rincian(); // Langsung tampilkan rincian & input pembayaran
  }
  else
  {
    cout << "Silakan pilih jenis rawat terlebih dahulu (menu 2).\n";
  }
}

void SistemBPJS::cetakStruk()
{
  if (jenisRawatDipilih == 1)
  {
    rawatInap.struk(); // ini manggil struk dari Rawatinap
  }
  else if (jenisRawatDipilih == 2)
  {
    rawatJalan.struk(); // ini manggil struk dari Rawatjalan
  }
  else
  {
    cout << "Silakan pilih jenis rawat dan lakukan pembayaran terlebih dahulu.\n";
  }
}

void SistemBPJS::tampilkanDataBPJS()
{
  ifstream file("bpjs.txt");
  if (!file.is_open())
  {
    cout << "Belum ada data layanan BPJS.\n";
    return;
  }

  string baris;
  int i = 1;

  cout << "\n==== DAFTAR DATA LAYANAN BPJS ====\n";
  while (getline(file, baris))
  {
    stringstream ss(baris);
    string waktu, id, nama, keluhan, poli;
    getline(ss, waktu, ';');
    getline(ss, id, ';');
    getline(ss, nama, ';');
    getline(ss, keluhan, ';');
    getline(ss, poli, ';');

    cout << "\nData ke-" << i++ << ":\n";
    cout << "Waktu     : " << waktu << "\n";
    cout << "ID Pasien : " << id << "\n";
    cout << "Nama      : " << nama << "\n";
    cout << "Keluhan   : " << keluhan << "\n";
    cout << "Poli      : " << poli << "\n";
  }

  file.close();
}

void SistemBPJS::cariData()
{
  string cariID;
  cout << "Masukkan ID Pasien yang dicari: ";
  getline(cin, cariID);

  ifstream file("bpjs.txt");
  string baris;
  bool ditemukan = false;

  while (getline(file, baris))
  {
    stringstream ss(baris);
    string waktu, id, nama, keluhan, poli;
    getline(ss, waktu, ';');
    getline(ss, id, ';');
    getline(ss, nama, ';');
    getline(ss, keluhan, ';');
    getline(ss, poli, ';');

    if (id == cariID)
    {
      cout << "\n==== Data Ditemukan ====\n";
      cout << "Waktu     : " << waktu << "\n";
      cout << "ID Pasien : " << id << "\n";
      cout << "Nama      : " << nama << "\n";
      cout << "Keluhan   : " << keluhan << "\n";
      cout << "Poli      : " << poli << "\n";
      ditemukan = true;
      break; // Hentikan setelah ditemukan
    }
  }

  if (!ditemukan)
  {
    cout << "Data tidak ditemukan.\n";
  }

  file.close();
}

void SistemBPJS::urutkanData()
{
  ifstream file("bpjs.txt");
  string data[100];
  int jumlahData = 0;
  string baris;

  while (getline(file, baris) && jumlahData < 100)
  {
    data[jumlahData++] = baris;
  }
  file.close();

  // Bubble sort berdasarkan ID Pasien (kolom ke-2)
  for (int i = 0; i < jumlahData - 1; i++)
  {
    for (int j = 0; j < jumlahData - i - 1; j++)
    {
      stringstream ss1(data[j]), ss2(data[j + 1]);
      string waktu1, id1, nama1, keluhan1, poli1;
      string waktu2, id2, nama2, keluhan2, poli2;

      getline(ss1, waktu1, ';');
      getline(ss1, id1, ';');

      getline(ss2, waktu2, ';');
      getline(ss2, id2, ';');

      if (id1 > id2)
      {
        string temp = data[j];
        data[j] = data[j + 1];
        data[j + 1] = temp;
      }
    }
  }
  cout << "\n==== DATA BPJS SETELAH DIURUTKAN BERDASARKAN ID PASIEN ====\n";
  for (int i = 0; i < jumlahData; i++)
  {
    stringstream ss(data[i]);
    string waktu, id, nama, keluhan, poli;

    getline(ss, waktu, ';');
    getline(ss, id, ';');
    getline(ss, nama, ';');
    getline(ss, keluhan, ';');
    getline(ss, poli, ';');

    cout << "\nData ke-" << (i + 1) << ":\n";
    cout << "Waktu     : " << waktu << "\n";
    cout << "ID Pasien : " << id << "\n";
    cout << "Nama      : " << nama << "\n";
    cout << "Keluhan   : " << keluhan << "\n";
    cout << "Poli      : " << poli << "\n";
  }
}

void SistemBPJS::menu()
{
  int pilihan;
  do
  {
    cout << "\n===== MENU LAYANAN BPJS =====\n";
    cout << "1. Pendaftaran Pasien BPJS\n";
    cout << "2. Pilih Jenis Rawat (Inap / Jalan)\n";
    cout << "3. Proses Pembayaran Layanan\n";
    cout << "4. Cetak Struk Pembayaran\n";
    cout << "5. Tampilkan Semua Data Pasien BPJS\n";
    cout << "6. Cari Data Pasien\n";
    cout << "7. Urutkan Data Pasien\n";
    cout << "8. Kembali ke Menu Utama\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    cin.ignore();

    switch (pilihan)
    {
    case 1:
      cin.ignore();
      PendaftaranBPJS();
      break;
    case 2:
      pilihRawat();
      break;
    case 3:
      prosesPembayaran();
      break;
    case 4:
      cetakStruk();
      break;
    case 5:
      tampilkanDataBPJS();
      break;
    case 6:
      cariData();
      break;
    case 7:
      urutkanData();
      break;
    case 8:
      cout << "Kembali ke menu utama.\n";
      break;
    default:
      cout << "Pilihan tidak valid.\n";
    }
  } while (pilihan != 8);
}

// SISTEM LAYANAN LABORATORIUM
class SistemLaboratorium
{
public:
  void menu();
  void pendaftaranLab();
  void tampilkanDataLab();
  void cariDataLab();
  void hapusDataLab();
  void cetakLaporanLab();

private:
  bool sudahDaftar(const string &idPasien);
};

bool SistemLaboratorium::sudahDaftar(const string &idPasien)
{
  ifstream file("lab.txt");
  string baris;
  while (getline(file, baris))
  {
    stringstream ss(baris);
    string waktu, id, nama;
    getline(ss, waktu, ';');
    getline(ss, id, ';');
    if (id == idPasien)
      return true;
  }
  return false;
}

void SistemLaboratorium::pendaftaranLab()
{
  string id, nama, jenisLab, keluhan, hasilTes;
  cout << "\n=== PENDAFTARAN LABORATORIUM ===\n";
  cout << "Masukkan ID Pasien: ";
  cin.ignore();
  getline(cin, id);

  ifstream filePasien("pasien.txt");
  bool ditemukan = false;
  string baris;
  while (getline(filePasien, baris))
  {
    stringstream ss(baris);
    string umurStr;
    string temp;
    getline(ss, nama, ';');
    getline(ss, temp, ';');
    if (temp == id)
    {
      ditemukan = true;
      break;
    }
  }
  filePasien.close();

  if (!ditemukan)
  {
    cout << "ID Pasien tidak ditemukan.\n";
    return;
  }
  if (sudahDaftar(id))
  {
    cout << "Pasien sudah terdaftar di layanan laboratorium.\n";
    return;
  }

  int pilihanLab;
  do
  {
    cout << "\nPilih Jenis Laboratorium:\n";
    cout << "1. Patologi Klinik\n";
    cout << "2. Mikrobiologi\n";
    cout << "3. Patologi Anatomi\n";
    cout << "Masukkan Pilihan (1-3): ";
    cin >> pilihanLab;
    cin.ignore();

    if (pilihanLab == 1)
      jenisLab = "Patologi Klinik";
    else if (pilihanLab == 2)
      jenisLab = "Mikrobiologi";
    else if (pilihanLab == 3)
      jenisLab = "Patologi Anatomi";
    else
      cout << "Pilihan tidak valid.\n";

  } while (pilihanLab < 1 || pilihanLab > 3);

  cout << "Hasil Tes: ";
  getline(cin, hasilTes);

  time_t now = time(0);
  string waktu = ctime(&now);
  waktu.pop_back();

  ofstream file("lab.txt", ios::app);
  file << waktu << ";" << id << ";" << nama << ";" << jenisLab << ";" << ";" << hasilTes << ";\n";
  file.close();

  cout << "\nPendaftaran berhasil dan data disimpan.\n";
}

void SistemLaboratorium::tampilkanDataLab()
{
  ifstream file("lab.txt");
  string baris;
  int i = 1;
  cout << "\n=== DATA LAYANAN LABORATORIUM ===\n";
  while (getline(file, baris))
  {
    stringstream ss(baris);
    string waktu, id, nama, jenisLab, keluhan, hasilTes;
    getline(ss, waktu, ';');
    getline(ss, id, ';');
    getline(ss, nama, ';');
    getline(ss, jenisLab, ';');
    getline(ss, hasilTes, ';');

    cout << "\nData ke-" << i++ << ":\n";
    cout << "Waktu        : " << waktu << endl;
    cout << "ID Pasien    : " << id << endl;
    cout << "Nama         : " << nama << endl;
    cout << "Jenis Lab    : " << jenisLab << endl;
    cout << "Hasil Tes    : " << hasilTes << endl;
  }
  file.close();
}

void SistemLaboratorium::cariDataLab()
{
  string keyword;
  cout << "Masukkan ID/Nama Pasien yang dicari: ";
  cin.ignore();
  getline(cin, keyword);

  ifstream file("lab.txt");
  string baris;
  bool ditemukan = false;

  while (getline(file, baris))
  {
    if (baris.find(keyword) != string::npos)
    {
      ditemukan = true;
      stringstream ss(baris);
      string waktu, id, nama, jenisLab, hasilTes;
      getline(ss, waktu, ';');
      getline(ss, id, ';');
      getline(ss, nama, ';');
      getline(ss, jenisLab, ';');
      getline(ss, hasilTes, ';');

      cout << "\nData ditemukan:\n";
      cout << "Waktu     : " << waktu << endl;
      cout << "ID        : " << id << endl;
      cout << "Nama      : " << nama << endl;
      cout << "Jenis Lab : " << jenisLab << endl;
      cout << "Hasil Tes : " << hasilTes << endl;
    }
  }
  if (!ditemukan)
    cout << "\nData tidak ditemukan.\n";
  file.close();
}

void SistemLaboratorium::hapusDataLab()
{
  string id;
  cout << "Masukkan ID Pasien yang datanya ingin dihapus: ";
  cin.ignore();
  getline(cin, id);

  ifstream file("lab.txt");
  ofstream temp("temp.txt");
  string baris;
  bool ditemukan = false;

  while (getline(file, baris))
  {
    if (baris.find(id) == string::npos)
    {
      temp << baris << endl;
    }
    else
    {
      ditemukan = true;
    }
  }
  file.close();
  temp.close();
  remove("lab.txt");
  rename("temp.txt", "lab.txt");

  if (ditemukan)
    cout << "Data berhasil dihapus.\n";
  else
    cout << "Data tidak ditemukan.\n";
}

void SistemLaboratorium::cetakLaporanLab()
{
  cout << "\n=== LAPORAN DATA LABORATORIUM ===\n";
  tampilkanDataLab();
}

void SistemLaboratorium::menu()
{
  int pilih;
  do
  {
    cout << "\n========= MENU SISTEM LABORATORIUM =========\n";
    cout << "1. Pendaftaran Lab\n";
    cout << "2. Tampilkan Data Lab\n";
    cout << "3. Cari Data Lab\n";
    cout << "4. Hapus Data Lab\n";
    cout << "5. Cetak Laporan Lab\n";
    cout << "6. Kembali\n";
    cout << "Pilihan Anda: ";
    cin >> pilih;

    switch (pilih)
    {
    case 1:
      pendaftaranLab();
      break;
    case 2:
      tampilkanDataLab();
      break;
    case 3:
      cariDataLab();
      break;
    case 4:
      hapusDataLab();
      break;
    case 5:
      cetakLaporanLab();
      break;
    case 6:
      cout << "Kembali ke menu utama...\n";
      break;
    default:
      cout << "Pilihan tidak valid.\n";
    }
  } while (pilih != 6);
}

// CLASS OBAT
const int MaxObat = 100;

class Obat{
private:
  string idObat;
  string namaObat;
  int stok;
  int harga;

public:
  Obat()  {
    idObat = "";
    namaObat = "";
    stok = 0;
    harga = 0;
  }

  void inputObat()  {
    cout << "ID Obat     : ";
    getline(cin, idObat);
    cout << "Nama Obat   : ";
    getline(cin, namaObat);
    cout << "Stok Obat   : ";
    cin >> stok;
    cout << "Harga Obat  : ";
    cin >> harga;
    cin.ignore();
  }

  void tampilkanDaftarObat() const  {
    cout << "ID Obat     : " << idObat << endl;
    cout << "Nama Obat   : " << namaObat << endl;
    cout << "Stok        : " << stok << endl;
    cout << "Harga       : Rp " << harga << endl;
    cout << "-----------------------------\n";
  }
  string getKode() { return idObat; }
  string getNama() { return namaObat; }
  int getStok() { return stok; }
  int getHarga() { return harga; }
  void kurangiStok(int jml) { stok -= jml; }
};

//SISTEM LAYANAN FARMASI
class SistemFarmasi{
private:
  Obat daftarObat[MaxObat];
  int jumlahObat = 0;
  string idPasienPesanan[100];
  string namaObatPesanan[100];
  int jumlahPesananObat[100];
  int totalHargaPesanan[100];
  int jumlahPesanan = 0;

public:
  void tampilkanDaftarObat();
  void tambahDaftarObat();
  void cariPesananObat();
  void buatPesananObat();
  void simpanDataObatKeFile();
  void ubahPesananObat();
  void Pembayaran();
  void cetakStrukPembayaran();
  void tampilkanSemuaPesanan();
  void totalPenjualanObat();
  void menuUrutkanPesanan();
  void urutkanPesananNama();
  void urutkanPesananID();
  void cariPesananNama();
  void cariPesananID();
  void menuCariPesanan();
  void simpanPesananKeFile();
  void menuFarmasi();
};

void SistemFarmasi::tampilkanDaftarObat(){
  cout << "\n=== DAFTAR OBAT TERSEDIA ===\n";

  if (jumlahObat == 0)  {
    cout << "Belum ada obat yang tersedia.\n";
    return;
  }

  cout << left << setw(5) << "No" << setw(10) << "Kode"
       << setw(25) << "Nama Obat"
       << setw(10) << "Stok"
       << setw(10) << "Harga\n";
  cout << "-----------------------------------------------------------\n";

  for (int i = 0; i < jumlahObat; i++)  {
    cout << left << setw(5) << (i + 1)
         << setw(10) << daftarObat[i].getKode()
         << setw(25) << daftarObat[i].getNama()
         << setw(10) << daftarObat[i].getStok()
         << "Rp" << daftarObat[i].getHarga() << endl;
  }
  cout << "-----------------------------------------------------------\n";
}

void SistemFarmasi::tambahDaftarObat(){
  char lanjut = 'y';
  while (lanjut == 'y' || lanjut == 'Y')  {
    if (jumlahObat >= MaxObat)    {
      cout << "Data obat penuh. Tidak bisa menambahkan lebih banyak.\n";
      break;
    }

    cout << "\n=== TAMBAH OBAT BARU ===\n";
    daftarObat[jumlahObat].inputObat();
    jumlahObat++;

    cout << "Obat berhasil ditambahkan!\n";
    simpanDataObatKeFile();

    cout << "Apakah ingin menambahkan lagi? (y/n): ";
    cin >> lanjut;
    cin.ignore();
  }
}

void SistemFarmasi::simpanDataObatKeFile()
{
  ofstream file("obat.txt");
  if (!file)
  {
    cout << "Gagal membuka file untuk menyimpan data obat.\n";
    return;
  }

  for (int i = 0; i < jumlahObat; i++)
  {
    file << daftarObat[i].getKode() << ";"
         << daftarObat[i].getNama() << ";"
         << daftarObat[i].getStok() << ";"
         << daftarObat[i].getHarga() << endl;
  }

  file.close();
  cout << "Data obat berhasil disimpan ke file 'obat.txt'.\n";
}

void SistemFarmasi::buatPesananObat()
{
  if (jumlahPesanan >= 100)
  {
    cout << "Data pesanan penuh!\n";
    return;
  }

  cout << "\n=== INPUT PESANAN OBAT ===\n";
  cout << "ID Pasien        : ";
  getline(cin, idPasienPesanan[jumlahPesanan]);
  cout << "Nama Obat        : ";
  getline(cin, namaObatPesanan[jumlahPesanan]);
  cout << "Jumlah Dipesan   : ";
  cin >> jumlahPesananObat[jumlahPesanan];
  cin.ignore();

  int harga = 0;
  bool ditemukan = false;
  for (int i = 0; i < jumlahObat; i++)
  {
    if (daftarObat[i].getNama() == namaObatPesanan[jumlahPesanan])
    {
      harga = daftarObat[i].getHarga();
      daftarObat[i].kurangiStok(jumlahPesananObat[jumlahPesanan]);
      ditemukan = true;
      break;
    }
  }

  if (!ditemukan)
  {
    cout << "Obat tidak ditemukan!\n";
    return;
  }

  totalHargaPesanan[jumlahPesanan] = harga * jumlahPesananObat[jumlahPesanan];
  cout << "Total Harga      : Rp " << totalHargaPesanan[jumlahPesanan] << endl;
  cout << "Pesanan berhasil disimpan!\n";
  jumlahPesanan++;
}

void SistemFarmasi::ubahPesananObat()
{
  cout << "\n=== UBAH PESANAN OBAT ===\n";
  if (jumlahPesanan == 0)
  {
    cout << "Belum ada pesanan untuk diubah.\n";
    return;
  }

  string idCari;
  cout << "Masukkan ID Pasien yang ingin diubah pesanannya: ";
  getline(cin, idCari);

  bool ditemukan = false;
  for (int i = 0; i < jumlahPesanan; i++)
  {
    if (idPasienPesanan[i] == idCari)
    {
      cout << "Pesanan ditemukan.\n";
      cout << "Nama Obat Lama   : " << namaObatPesanan[i] << endl;
      cout << "Jumlah Lama      : " << jumlahPesananObat[i] << endl;

      cout << "\nMasukkan Data Baru:\n";
      cout << "Nama Obat Baru   : ";
      getline(cin, namaObatPesanan[i]);
      cout << "Jumlah Baru      : ";
      cin >> jumlahPesananObat[i];
      cin.ignore();

      int hargaBaru = 0;
      bool obatAda = false;
      for (int j = 0; j < jumlahObat; j++)      {
        if (daftarObat[j].getNama() == namaObatPesanan[i])        {
          hargaBaru = daftarObat[j].getHarga();
          obatAda = true;
          break;
        }
      }

      if (!obatAda)      {
        cout << "Nama obat tidak ditemukan di daftar. Perubahan dibatalkan.\n";
        return;
      }

      totalHargaPesanan[i] = hargaBaru * jumlahPesananObat[i];
      cout << "Total Harga Baru: Rp " << totalHargaPesanan[i] << endl;
      cout << "Pesanan berhasil diubah.\n";
      ditemukan = true;
      break;
    }
  }

  if (!ditemukan)  {
    cout << "Pesanan dengan ID Pasien tersebut tidak ditemukan.\n";
  }
}

void SistemFarmasi::Pembayaran(){
  cout << "\n=== PEMBAYARAN PESANAN OBAT ===\n";
  if (jumlahPesanan == 0)  {
    cout << "Belum ada pesanan yang bisa dibayar.\n";
    return;
  }

  string idCari;
  cout << "Masukkan ID Pasien yang akan membayar: ";
  getline(cin, idCari);

  bool ditemukan = false;
  for (int i = 0; i < jumlahPesanan; i++)  {
    if (idPasienPesanan[i] == idCari)    {
      int hargaSatuan = totalHargaPesanan[i] / jumlahPesananObat[i];
      cout << "Nama Obat     : " << namaObatPesanan[i] << endl;
      cout << "Jumlah        : " << jumlahPesananObat[i] << endl;
      cout << "Harga Satuan  : Rp " << hargaSatuan << endl;
      cout << "Total Tagihan : Rp " << totalHargaPesanan[i] << endl;

      int bayar;
      cout << "Masukkan jumlah uang yang dibayar: Rp ";
      cin >> bayar;
      cin.ignore();

      if (bayar < totalHargaPesanan[i])      {
        cout << "Uang tidak cukup! Pembayaran gagal.\n";
        return;
      }

      int kembalian = bayar - totalHargaPesanan[i];
      cout << "Pembayaran berhasil!\n";
      cout << "Kembalian : Rp " << kembalian << endl;
      cout << "Pilih menu 'Cetak Struk' untuk melihat struk.\n";
      ditemukan = true;
      break;
    }
  }
  if (!ditemukan)  {
    cout << "ID Pasien tidak ditemukan dalam daftar pesanan.\n";
  }
}

void SistemFarmasi::cetakStrukPembayaran(){
  cout << "\n=== CETAK STRUK PEMBAYARAN ===\n";
  if (jumlahPesanan == 0)  {
    cout << "Belum ada pesanan yang bisa dicetak struknya.\n";
    return;
  }

  string idCari;
  cout << "Masukkan ID Pasien: ";
  getline(cin, idCari);

  bool ditemukan = false;
  for (int i = 0; i < jumlahPesanan; i++)  {
    if (idPasienPesanan[i] == idCari)    {
      int hargaSatuan = totalHargaPesanan[i] / jumlahPesananObat[i];

      cout << "\n======== STRUK PEMBAYARAN ========\n";
      cout << "ID Pasien    : " << idPasienPesanan[i] << endl;
      cout << "Nama Obat    : " << namaObatPesanan[i] << endl;
      cout << "Jumlah       : " << jumlahPesananObat[i] << endl;
      cout << "Harga Satuan : Rp " << hargaSatuan << endl;
      cout << "Total Bayar  : Rp " << totalHargaPesanan[i] << endl;
      cout << "Status       : LUNAS\n";
      cout << "==================================\n";

      // Simpan ke file
      ofstream file("farmasi.txt", ios::app);
      if (file.is_open()) {
        file << "========== STRUK FARMASI ==========\n";
        file << "ID Pasien    : " << idPasienPesanan[i] << "\n";
        file << "Nama Obat    : " << namaObatPesanan[i] << "\n";
        file << "Jumlah       : " << jumlahPesananObat[i] << "\n";
        file << "Harga Satuan : Rp " << hargaSatuan << "\n";
        file << "Total Bayar  : Rp " << totalHargaPesanan[i] << "\n";
        file << "Status       : LUNAS\n";
        file << "===================================\n\n";
        file.close();
        cout << "Struk juga disimpan di file 'farmasi.txt'.\n";
      } else {
        cout << "Gagal menyimpan struk ke file.\n";
      }
      
      ditemukan = true;
      break;
    }
  }

  if (!ditemukan)  {
    cout << "Data pesanan tidak ditemukan.\n";
  }
}

void SistemFarmasi::tampilkanSemuaPesanan(){
  cout << "\n=== DAFTAR SEMUA PESANAN OBAT ===\n";

  if (jumlahPesanan == 0)  {
    cout << "Belum ada data pesanan obat.\n";
    return;
  }

  cout << left << setw(5) << "No"
       << setw(15) << "ID Pasien"
       << setw(25) << "Nama Obat"
       << setw(10) << "Jumlah"
       << setw(15) << "Total Harga" << endl;
  cout << "--------------------------------------------------------------------------\n";

  for (int i = 0; i < jumlahPesanan; i++) {
    cout << left << setw(5) << (i + 1)
         << setw(15) << idPasienPesanan[i]
         << setw(25) << namaObatPesanan[i]
         << setw(10) << jumlahPesananObat[i]
         << "Rp " << totalHargaPesanan[i] << endl;
  }

  cout << "--------------------------------------------------------------------------\n";
}

void SistemFarmasi::simpanPesananKeFile(){
  ofstream file("data_pesanan.txt");

  if (!file.is_open())  {
    cout << "Gagal membuka file untuk menyimpan pesanan.\n";
    return;
  }

  for (int i = 0; i < jumlahPesanan; i++)  {
    file << idPasienPesanan[i] << ";"
         << namaObatPesanan[i] << ";"
         << jumlahPesananObat[i] << ";"
         << totalHargaPesanan[i] << "\n";
  }

  file.close();
  cout << "Data pesanan berhasil disimpan ke file.\n";
}

void SistemFarmasi::totalPenjualanObat(){
  cout << "\n=== TOTAL PENJUALAN OBAT ===\n";

  if (jumlahPesanan == 0)  {
    cout << "Belum ada pesanan yang dilakukan.\n";
    return;
  }

  int totalSeluruh = 0;

  cout << left << setw(15) << "ID Pasien"
       << setw(25) << "Nama Obat"
       << setw(10) << "Jumlah"
       << setw(15) << "Total Harga\n";
  cout << "-------------------------------------------------------------\n";

  for (int i = 0; i < jumlahPesanan; i++)  {
    cout << left << setw(15) << idPasienPesanan[i]
         << setw(25) << namaObatPesanan[i]
         << setw(10) << jumlahPesananObat[i]
         << "Rp" << totalHargaPesanan[i] << endl;
    totalSeluruh += totalHargaPesanan[i];
  }

  cout << "-------------------------------------------------------------\n";
  cout << "TOTAL SELURUH PENJUALAN OBAT: Rp" << totalSeluruh << endl;
}

void SistemFarmasi::urutkanPesananNama(){
  for (int i = 0; i < jumlahPesanan - 1; i++)  {
    for (int j = 0; j < jumlahPesanan - i - 1; j++)    {
      if (namaObatPesanan[j] > namaObatPesanan[j + 1])      {
        // Simpan data ke variabel sementara
        string tempNama = namaObatPesanan[j];
        string tempID = idPasienPesanan[j];
        int tempJumlah = jumlahPesananObat[j];
        int tempTotal = totalHargaPesanan[j];

        // Geser elemen ke kiri
        namaObatPesanan[j] = namaObatPesanan[j + 1];
        idPasienPesanan[j] = idPasienPesanan[j + 1];
        jumlahPesananObat[j] = jumlahPesananObat[j + 1];
        totalHargaPesanan[j] = totalHargaPesanan[j + 1];

        // Masukkan kembali dari temp
        namaObatPesanan[j + 1] = tempNama;
        idPasienPesanan[j + 1] = tempID;
        jumlahPesananObat[j + 1] = tempJumlah;
        totalHargaPesanan[j + 1] = tempTotal;
      }
    }
  }
  cout << "\nData berhasil diurutkan berdasarkan Nama Obat.\n";
  tampilkanSemuaPesanan();
}

void SistemFarmasi::urutkanPesananID(){
  for (int i = 0; i < jumlahPesanan - 1; i++){
    for (int j = 0; j < jumlahPesanan - i - 1; j++){
      if (idPasienPesanan[j] > idPasienPesanan[j + 1])      {
        string tempNama = namaObatPesanan[j];
        string tempID = idPasienPesanan[j];
        int tempJumlah = jumlahPesananObat[j];
        int tempTotal = totalHargaPesanan[j];

        namaObatPesanan[j] = namaObatPesanan[j + 1];
        idPasienPesanan[j] = idPasienPesanan[j + 1];
        jumlahPesananObat[j] = jumlahPesananObat[j + 1];
        totalHargaPesanan[j] = totalHargaPesanan[j + 1];

        namaObatPesanan[j + 1] = tempNama;
        idPasienPesanan[j + 1] = tempID;
        jumlahPesananObat[j + 1] = tempJumlah;
        totalHargaPesanan[j + 1] = tempTotal;
      }
    }
  }
  cout << "\nData berhasil diurutkan berdasarkan ID Pasien.\n";
  tampilkanSemuaPesanan();
}

void SistemFarmasi::menuUrutkanPesanan(){
  int pilih;
  do  {
    cout << "\n+===============================================+\n";
    cout << "|              SORTING PESANAN OBAT             |\n";
    cout << "+===============================================+\n";
    cout << "| 1. Urutkan Berdasarkan Nama Obat              |\n";
    cout << "| 2. Urutkan Berdasarkan ID Pasien              |\n";
    cout << "| 3. Kembali ke Menu Utama                      |\n";
    cout << "+-----------------------------------------------+\n";
    cout << "| Masukkan Pilihan Anda: ";
    cin >> pilih;
    cin.ignore();

    switch (pilih)    {
    case 1:
      urutkanPesananNama();
      break;
    case 2:
      urutkanPesananID();
      break;
    case 3:
      cout << "Kembali ke menu utama...\n";
      break;
    default:
      cout << "Pilihan tidak valid!\n";
    }
  } while (pilih != 3);
}

void SistemFarmasi::cariPesananNama(){
  if (jumlahPesanan == 0)  {
    cout << "Belum ada data pesanan.\n";
    return;
  }
  urutkanPesananNama();

  string cariNama;
  cout << "Masukkan nama obat yang ingin dicari: ";
  getline(cin, cariNama);

  int kiri = 0, kanan = jumlahPesanan - 1;
  bool ditemukan = false;

  while (kiri <= kanan)
  {
    int tengah = (kiri + kanan) / 2;
    if (namaObatPesanan[tengah] == cariNama)
    {
      cout << "\n=== PESANAN DENGAN NAMA OBAT: " << cariNama << " ===\n";
      cout << "ID Pasien     | Nama Obat              | Jumlah | Total\n";
      cout << "----------------------------------------------------------\n";

      // Telusuri ke kiri dari tengah
      int i = tengah;
      while (i >= 0 && namaObatPesanan[i] == cariNama)      {
        cout << idPasienPesanan[i] << " | " << namaObatPesanan[i]
             << " | " << jumlahPesananObat[i]
             << "     | Rp" << totalHargaPesanan[i] << endl;
        i--;
      }

      // Telusuri ke kanan dari tengah
      i = tengah + 1;
      while (i < jumlahPesanan && namaObatPesanan[i] == cariNama)      {
        cout << idPasienPesanan[i] << " | " << namaObatPesanan[i]
             << " | " << jumlahPesananObat[i]
             << "     | Rp" << totalHargaPesanan[i] << endl;
        i++;
      }

      ditemukan = true;
      break;
    }
    else if (namaObatPesanan[tengah] < cariNama)    {
      kiri = tengah + 1;
    }
    else    {
      kanan = tengah - 1;
    }
  }

  if (!ditemukan)  {
    cout << "Pesanan dengan nama obat '" << cariNama << "' tidak ditemukan.\n";
  }
}

void SistemFarmasi::cariPesananID(){
  if (jumlahPesanan == 0)
  {
    cout << "Belum ada data pesanan.\n";
    return;
  }
  // Urutkan data berdasarkan ID pasien sebelum melakukan binary search
  urutkanPesananID();

  string cariID;
  cout << "Masukkan ID Pasien yang ingin dicari: ";
  getline(cin, cariID);

  int kiri = 0, kanan = jumlahPesanan - 1;
  bool ditemukan = false;

  while (kiri <= kanan)  {
    int tengah = (kiri + kanan) / 2;

    if (idPasienPesanan[tengah] == cariID)    {
      cout << "\n=== DATA PESANAN UNTUK ID PASIEN: " << cariID << " ===\n";
      cout << "ID Pasien : Nama Obat : Jumlah : Total\n";
      cout << "-----------------------------------------\n";

      // Telusuri ke kiri
      int i = tengah;
      while (i >= 0 && idPasienPesanan[i] == cariID)
      {
        cout << idPasienPesanan[i] << " : " << namaObatPesanan[i]
             << " : " << jumlahPesananObat[i]
             << " : Rp" << totalHargaPesanan[i] << endl;
        i--;
      }

      // Telusuri ke kanan
      i = tengah + 1;
      while (i < jumlahPesanan && idPasienPesanan[i] == cariID)
      {
        cout << idPasienPesanan[i] << " : " << namaObatPesanan[i]
             << " : " << jumlahPesananObat[i]
             << " : Rp" << totalHargaPesanan[i] << endl;
        i++;
      }

      ditemukan = true;
      break;
    }
    else if (idPasienPesanan[tengah] < cariID)    {
      kiri = tengah + 1;
    }    
    else    {
      kanan = tengah - 1;
    }
  }

  if (!ditemukan)  {
    cout << "Data pesanan dengan ID pasien '" << cariID << "' tidak ditemukan.\n";
  }
}

void SistemFarmasi::menuCariPesanan(){
  int pilih;
  do  {
    cout << "\n+===============================================+\n";
    cout << "|             SEARCHING PESANAN OBAT            |\n";
    cout << "+===============================================+\n";
    cout << "| 1. Cari Berdasarkan Nama Obat                 |\n";
    cout << "| 2. Cari Berdasarkan ID Pasien                 |\n";
    cout << "| 3. Kembali ke Menu Utama                      |\n";
    cout << "+-----------------------------------------------+\n";
    cout << "| Masukkan Pilihan Anda: ";
    cin >> pilih;
    cin.ignore();

    switch (pilih)    {
    case 1:
      cariPesananNama();
      break;
    case 2:
      cariPesananID();
      break;
    case 3:
      cout << "Kembali ke menu utama...\n";
      break;
    default:
      cout << "Pilihan tidak valid!\n";
    }
  } while (pilih != 3);
}

void SistemFarmasi::menuFarmasi(){
  int pilihan;
  do {
    cout << "\n+===============================================+\n";
    cout << "|             SISTEM LAYANAN FARMASI            |\n";
    cout << "+===============================================+\n";
    cout << "| 1.  Tampilkan Daftar Obat                     |\n";
    cout << "| 2.  Tambah Daftar Obat                        |\n";
    cout << "| 3.  Input Pesanan Obat                        |\n";
    cout << "| 4.  Ubah Pesanan Obat                         |\n";
    cout << "| 5.  Pembayaran                                |\n";
    cout << "| 6.  Cetak Struk Pembayaran                    |\n";
    cout << "| 7.  Tampilkan Semua Pesanan                   |\n";
    cout << "| 8.  Urutkan Pesanan Obat                      |\n";
    cout << "| 9.  Cari Pesanan Obat                         |\n";
    cout << "| 10. Total Penjualan Obat                      |\n";
    cout << "| 11. Keluar                                    |\n";
    cout << "+===============================================+\n";
    cout << "| Masukkan Pilihan Anda: ";
    cin >> pilihan;
    cin.ignore();

    switch (pilihan)
    {
    case 1:
      tampilkanDaftarObat();
      break;
    case 2:
      tambahDaftarObat();
      break;
    case 3:
      buatPesananObat();
      break;
    case 4:
      ubahPesananObat();
      break;
    case 5:
      Pembayaran();
      break;
    case 6:
      cetakStrukPembayaran();
      break;
    case 7:
      tampilkanSemuaPesanan();
      break;
    case 8:
      menuUrutkanPesanan();
      break;
    case 9:
      menuCariPesanan();
      break;
    case 10:
      totalPenjualanObat();
      break;
    case 11:
      cout << "Keluar dari Sistem Farmasi.\n";
      break;
    default:
      cout << "Pilihan tidak valid!\n";
      break;
    }
  } while (pilihan != 11);
}

class SistemKasir
{
public:
  void menuKasir();

private:
  void tampilkanSemuaTransaksi();
  void cariTransaksiPasien();
  void totalPemasukan();
};

void SistemKasir::menuKasir(){
  int pilih;
  do  {
    cout << "\n+=======================================+\n";
    cout << "|             MENU KASIR               |\n";
    cout << "+=======================================+\n";
    cout << "| 1. Lihat Semua Transaksi             |\n";
    cout << "| 2. Cari Transaksi Pasien             |\n";
    cout << "| 3. Total Seluruh Pemasukan           |\n";
    cout << "| 4. Keluar                            |\n";
    cout << "+---------------------------------------+\n";
    cout << "Pilih menu: ";
    cin >> pilih;
    cin.ignore();

    switch (pilih)
    {
    case 1:
      tampilkanSemuaTransaksi();
      break;
    case 2:
      cariTransaksiPasien();
      break;
    case 3:
      totalPemasukan();
      break;
    case 4:
      cout << "Kembali ke menu utama...\n";
      break;
    default:
      cout << "Pilihan tidak valid!\n";
    }
  } while (pilih != 4);
}

void SistemKasir::tampilkanSemuaTransaksi()
{
  cout << "\n=== SEMUA TRANSAKSI PEMBAYARAN ===\n";
  string layanan[] = {"farmasi.txt", "bpjs_struk.txt", "umum_struk.txt"};

  for (string namaFile : layanan)
  {
    ifstream file(namaFile);
    cout << "\n--- Transaksi dari " << namaFile << " ---\n";
    if (!file)
    {
      cout << "Tidak ada data.\n";
      continue;
    }
    string baris;
    while (getline(file, baris))
    {
      cout << baris << endl;
    }
    file.close();
  }
}

void SistemKasir::cariTransaksiPasien()
{
  string idCari;
  cout << "Masukkan ID Pasien: ";
  getline(cin, idCari);

  string layanan[] = {"farmasi_struk.txt", "bpjs_struk.txt", "umum_struk.txt"};
  bool ditemukan = false;

  for (string namaFile : layanan)
  {
    ifstream file(namaFile);
    if (!file)
      continue;

    string baris;
    cout << "\n--- Dari " << namaFile << " ---\n";
    while (getline(file, baris))
    {
      if (baris.find(idCari) != string::npos)
      {
        cout << baris << endl;
        ditemukan = true;
      }
    }
    file.close();
  }

  if (!ditemukan)
    cout << "Data tidak ditemukan dalam semua layanan.\n";
}

void SistemKasir::totalPemasukan()
{
  string layanan[] = {"farmasi_struk.txt", "bpjs.txt", "umum.txt"};
  int total = 0;

  for (string namaFile : layanan)
  {
    ifstream file(namaFile);
    if (!file)
      continue;
    string baris;
    while (getline(file, baris))
    {
      if (baris.find("Total Bayar") != string::npos)
      {
        size_t pos = baris.find("Rp");
        if (pos != string::npos)
        {
          string nominal = baris.substr(pos + 2);
          total += stoi(nominal);
        }
      }
    }
    file.close();
  }

  cout << "\nTotal Seluruh Pemasukan dari Semua Layanan: Rp " << total << endl;
}

void MenuAdmin::sistemLayanan()
{
  int layanan;
  do
  {
    cout << "\n+=============================================+\n";
    cout << "|           SISTEM LAYANAN RUMAH SAKIT        |\n";
    cout << "+=============================================+\n";
    cout << "| 1. IGD                                      |\n";
    cout << "| 2. UMUM                                     |\n";
    cout << "| 3. BPJS                                     |\n";
    cout << "| 4. Laboratorium                             |\n";
    cout << "| 5. Farmasi                                  |\n";
    cout << "| 6. Kasir                                    |\n";
    cout << "| 7. Keluar                                   |\n";
    cout << "+=============================================+\n";
    cout << "Masukkan Pilihan Anda : ";
    cin >> layanan;
    cin.ignore();

    switch (layanan)
    {
    case 1:
    {
      SistemIGD igd;
      igd.menu();
      break;
    }
    case 2:
    {
      SistemUmum umum;
      umum.menu();
      break;
    }
    case 3:
    {
      SistemBPJS bpjs;
      bpjs.menu();
      break;
    }
    case 4:
    {
      SistemLaboratorium lab;
      lab.menu();
      break;
    }
    case 5:
    {
      SistemFarmasi farmasi;
      farmasi.menuFarmasi();
    }
    case 6:{
      SistemKasir kasir;
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
}

void MenuAdmin::editPasien()
{
  string id;
  cin.ignore();
  cout << "Masukkan ID pasien yang ingin diedit : ";
  getline(cin, id);
  Pasien::editPasien(id);
}

void MenuAdmin::hapusPasien()
{
  string id;
  cout << "Masukkan ID Pasien yang ingin dihapus: ";
  getline(cin, id);
  Pasien::hapusPasien(id);
}

void MenuAdmin::urutkanPasien()
{
  char ulangi;
  do
  {
    int kriteria, urutan;

    cout << "\n+===============================================+\n";
    cout << "|           MENU SORTING DATA PASIEN            |\n";
    cout << "+===============================================+\n";
    cout << "| Urutkan Data Pasien berdasarkan:              |\n";
    cout << "| 1. ID Pasien                                  |\n";
    cout << "| 2. Nama Pasien                                |\n";
    cout << "| 3. Umur Pasien                                |\n";
    cout << "+-----------------------------------------------+\n";
    cout << "| Masukkan Pilihan Anda : "; 
    cin >> kriteria;

    cout << "+===============================================+\n";
    cout << "| Urutkan secara:                               |\n";
    cout << "| 1. Ascending                                  |\n";
    cout << "| 2. Descending                                 |\n";
    cout << "+-----------------------------------------------+\n";
    cout << "| Masukkan Pilihan Anda : "; 
    cin >> urutan;
    cin.ignore();

    bool ascending = (urutan == 1);

    cout << "\nPenjelasan Urutan:\n";
    if (kriteria == 1)
    {
      cout << "Anda memilih urut berdasarkan ID Pasien.\n";
      if (ascending)
        cout << "Urutannya dari ID terkecil (RM0001) ke terbesar "
                "(RM9999).\n";
      else
        cout << "Urutannya dari ID terbesar (RM9999) ke terkecil "
                "(RM0001).\n";
    }
    else if (kriteria == 2)
    {
      cout << "Anda memilih urut berdasarkan Nama Pasien.\n";
      if (ascending)
        cout << "Urutannya dari A ke Z (alfabet naik).\n";
      else
        cout << "Urutannya dari Z ke A (alfabet turun).\n";
    }
    else if (kriteria == 3)
    {
      cout << "Anda memilih urut berdasarkan Umur Pasien.\n";
      if (ascending)
        cout << "Urutannya dari umur termuda ke tertua.\n";
      else
        cout << "Urutannya dari umur tertua ke termuda.\n";
    }
    else
    {
      cout << "Pilihan tidak valid. Kembali ke menu.\n";
      break;
    }

    // Proses Pengurutan
    Pasien::urutkanPasien(kriteria, ascending);

    cout << "\nIngin mengurutkan lagi? (y/n): ";
    cin >> ulangi;
    cin.ignore();

  } while (ulangi == 'y' || ulangi == 'Y');
}

// fungsi Login Menu Admin
bool loginAdmin(const string &user, const string &pass)
{
  return user == "admin" && pass == "admin123";
}

void menuAdmin()
{
  string user, pass;
  cout << "\nUsername : ";
  getline(cin, user);
  cout << "Password : ";
  getline(cin, pass);
  if (loginAdmin(user, pass))
  {
    MenuAdmin m;
    m.tampilMenu();
  }
  else
  {
    cout << "Login gagal.\n";
  }
}

void MenuAdmin::tampilMenu(){
  int pilihan;
  do  {
    cout << "\n  ==========================================================\n";
    cout << "||                SELAMAT DATANG DI SISTEM                  ||\n";
    cout << "||                  MANAJEMEN RUMAH SAKIT                   ||\n";
    cout << "||==========================================================||\n";
    cout << "|| 1. Pendaftaran Pasien                                    ||\n";
    cout << "|| 2. Menu Sistem Layanan                                   ||\n";
    cout << "|| 3. Edit Data Pasien                                      ||\n";
    cout << "|| 4. Hapus Data Pasien                                     ||\n";
    cout << "|| 5. Tampilkan Data Pasien                                 ||\n";
    cout << "|| 6. Cari Data Pasien                                      ||\n";
    cout << "|| 7. Urutkan Data Pasien                                   ||\n";
    cout << "|| 8. Logout                                                ||\n";
    cout << "  ==========================================================\n";
    cout << "Masukkan Pilihan Anda : ";
    cin >> pilihan;
    cin.ignore();

    switch (pilihan){
    case 1:{
      pendaftaranPasien();
      break;
    }
    case 2:{
      sistemLayanan();
      break;
    }
    case 3:{
      editPasien();
      break;
    }
    case 4:{
      hapusPasien();
      break;
    }
    case 5:
      Pasien::tampilkanSemua();
      break;
    case 6:{
      Pasien::cariPasien();
      break;
    }
    case 7:{
      urutkanPasien();
      break;
    }
    case 8:
      cout << "Terima kasih telah menggunakan sistem.\n";
      break;
    default:
      cout << "Pilihan tidak valid.\n";
    }
  } while (pilihan != 8);
}

int main(){
  int pilihan;
  do{
    cout << "\n---------------------------------------------\n";
    cout << "|                MENU UTAMA                 |\n";
    cout << "---------------------------------------------\n";
    cout << "| 1. Login Admin                            |\n";
    cout << "| 0. Keluar                                 |\n";
    cout << "---------------------------------------------\n";
    cout << "Pilih menu: ";
    cin >> pilihan;
    cin.ignore();

    switch (pilihan){
    case 1:
      menuAdmin();
      break;
    case 0:
      cout << "Terima kasih.\n";
      break;
    default:
      cout << "Pilihan tidak valid.\n";
    }
  } while (pilihan != 0);

  return 0;
}
