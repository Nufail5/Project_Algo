#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std

struct Booking {
    int id;
    string nama, lapangan;
    int tanggal, jam;
    Booking *next;
};

Booking *head = NULL;
Booking *tail = NULL;

bool cekID(int id){
    Booking *bantu = head;
    while(bantu != NULL){
        if(bantu->id == id) return true;
        bantu = bantu->next;
    }
    return false;
}

int inputAngka(string pesan){
    int x;
    while(true){
        cout << pesan;
        cin >> x;
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input harus angka!\n";
        } else break;
    }
    cin.ignore();
    return x;
}

string inputString(string pesan){
    string x;
    do{
        cout << pesan;
        getline(cin, x);
        if(x == "") cout << "Tidak boleh kosong!\n";
    }while(x == "");
    return x;
}

void tambahBooking(int id, string nama, string lapangan, int tanggal, int jam){
    Booking *baru = new Booking;
    baru->id = id;
    baru->nama = nama;
    baru->lapangan = lapangan;
    baru->tanggal = tanggal;
    baru->jam = jam;
    baru->next = NULL;

    if(head == NULL) head = tail = baru;
    else {
        tail->next = baru;
        tail = baru;
    }

    cout << "Booking berhasil ditambahkan!\n";
}

void tambahBookingFile(int id, string nama, string lapangan, int tanggal, int jam){
    Booking *baru = new Booking;
    baru->id = id;
    baru->nama = nama;
    baru->lapangan = lapangan;
    baru->tanggal = tanggal;
    baru->jam = jam;
    baru->next = NULL;

    if(head == NULL) head = tail = baru;
    else {
        tail->next = baru;
        tail = baru;
    }
}

void tampil(){
    if(head == NULL){
        cout << "\nData kosong!\n";
        return;
    }

    cout << "\n===========================================================\n";
    cout << left << setw(5) << "No"
         << setw(5) << "ID"
         << setw(20) << "Nama"
         << setw(15) << "Lapangan"
         << setw(10) << "Tanggal"
         << setw(5) << "Jam" << endl;
    cout << "===========================================================\n";

    Booking *bantu = head;
    int no = 1;

    while(bantu != NULL){
        cout << left << setw(5) << no++
             << setw(5) << bantu->id
             << setw(20) << bantu->nama
             << setw(15) << bantu->lapangan
             << setw(10) << bantu->tanggal
             << setw(5) << bantu->jam << endl;
        bantu = bantu->next;
    }

    cout << "===========================================================\n";
}

void cari(string nama){
    Booking *bantu = head;
    while(bantu != NULL){
        if(bantu->nama == nama){
            cout << "\nData ditemukan:\n";
            cout << "ID       : " << bantu->id << endl;
            cout << "Nama     : " << bantu->nama << endl;
            cout << "Lapangan : " << bantu->lapangan << endl;
            cout << "Tanggal  : " << bantu->tanggal << endl;
            cout << "Jam      : " << bantu->jam << endl;
            return;
        }
        bantu = bantu->next;
    }
    cout << "Data tidak ditemukan\n";
}

void sortNama(){
    Booking *i, *j;
    for(i = head; i != NULL; i = i->next){
        for(j = i->next; j != NULL; j = j->next){
            if(i->tanggal > j->tanggal || 
              (i->tanggal == j->tanggal && i->jam > j->jam)){
                swap(i->id, j->id);
                swap(i->nama, j->nama);
                swap(i->lapangan, j->lapangan);
                swap(i->tanggal, j->tanggal);
                swap(i->jam, j->jam);
            }
        }
    }
    cout << "Data sudah diurutkan berdasarkan tanggal & jam\n";
}

void hapus(int nomor){
    if(head == NULL){
        cout << "Data kosong!\n";
        return;
    }

    Booking *bantu = head;
    Booking *prev = NULL;
    int no = 1;

    while(bantu != NULL && no != nomor){
        prev = bantu;
        bantu = bantu->next;
        no++;
    }

    if(bantu == NULL){
        cout << "Nomor tidak ditemukan!\n";
        return;
    }

    if(prev == NULL) head = bantu->next;
    else prev->next = bantu->next;

    if(bantu == tail) tail = prev;

    delete bantu;
    cout << "Data berhasil dihapus\n";
}

void edit(int nomor){
    Booking *bantu = head;
    int no = 1;

    while(bantu != NULL && no != nomor){
        bantu = bantu->next;
        no++;
    }

    if(bantu == NULL){
        cout << "Data tidak ditemukan!\n";
        return;
    }

    cout << "\nMasukkan data baru:\n";

    int id;
    do{
        id = inputAngka("ID baru: ");
        if(id != bantu->id && cekID(id)){
            cout << "ID sudah ada!\n";
        }
    }while(id != bantu->id && cekID(id));

    bantu->id = id;
    bantu->nama = inputString("Nama baru: ");
    bantu->lapangan = inputString("Lapangan baru: ");
    bantu->tanggal = inputAngka("Tanggal baru: ");
    bantu->jam = inputAngka("Jam baru: ");

    cout << "Data berhasil diupdate\n";
}

void simpanFile(){
    ofstream file("booking.txt");

    Booking *bantu = head;
    while(bantu != NULL){
        file << bantu->id << ","
             << bantu->nama << ","
             << bantu->lapangan << ","
             << bantu->tanggal << ","
             << bantu->jam << endl;
        bantu = bantu->next;
    }

    cout << "Data berhasil disimpan\n";
}

void bacaFile(){
    ifstream file("booking.txt");
    if(!file){
        cout << "File belum ada!\n";
        return;
    }

    while(head != NULL){
        Booking *hapus = head;
        head = head->next;
        delete hapus;
    }
    tail = NULL;

    int id, tanggal, jam;
    string nama, lapangan;
    char koma;

    while(file >> id >> koma){
        getline(file, nama, ',');
        getline(file, lapangan, ',');
        file >> tanggal >> koma >> jam;
        file.ignore();

        tambahBookingFile(id, nama, lapangan, tanggal, jam);
    }

    cout << "Data berhasil dibaca\n";
}

int main(){
    int pilih;

    do{
        cout << "\n=================================\n";
        cout << "      BOOKING LAPANGAN\n";
        cout << "=================================\n";
        cout << "1. Tambah Booking\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Cari Data\n";
        cout << "4. Sorting Tanggal & Jam\n";
        cout << "5. Simpan ke File\n";
        cout << "6. Baca dari File\n";
        cout << "7. Hapus Data\n";
        cout << "8. Edit Data\n";
        cout << "0. Keluar\n";
        cout << "=================================\n";

        pilih = inputAngka("Pilih menu: ");

        if(pilih == 1){
            int id;
            do{
                id = inputAngka("ID: ");
                if(cekID(id)) cout << "ID sudah ada!\n";
            }while(cekID(id));

            string nama = inputString("Nama: ");
            string lapangan = inputString("Lapangan: ");
            int tanggal = inputAngka("Tanggal: ");
            int jam = inputAngka("Jam: ");

            tambahBooking(id, nama, lapangan, tanggal, jam);
        }
        else if(pilih == 2) tampil();
        else if(pilih == 3){
            string nama = inputString("Cari nama: ");
            cari(nama);
        }
        else if(pilih == 4) sortNama();
        else if(pilih == 5) simpanFile();
        else if(pilih == 6) bacaFile();
        else if(pilih == 7){
            tampil();
            int no = inputAngka("Nomor yang dihapus: ");
            hapus(no);
        }
        else if(pilih == 8){
            tampil();
            int no = inputAngka("Nomor yang diedit: ");
            edit(no);
        }

    }while(pilih != 0);

    while(head != NULL){
        Booking *hapus = head;
        head = head->next;
        delete hapus;
    }

    cout << "Terima kasih!\n";
    return 0;
}
