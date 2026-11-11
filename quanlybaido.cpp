#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg) {}

int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }

double phuong_tien::tinh_phi() const {
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
    for (int h = 0; h < tg_do; ++h) {
        if (h < 2) tong += gia * (cao_diem ? 1.30 : 0.95);
        else       tong += gia * 0.90;
    }
    return tong;
}

void phuong_tien::hien_thi() const {
    cout << "  ID: " << ma_xe << " | " << loai_xe
         << " | " << gio_vao << "h | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2) << tinh_phi() << "\n";
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    static const int so_xe = 3;
    phuong_tien pt[so_xe] ;   // sau này dùng m?ng
    int tong_xe;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    bool da_day() const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
    void hien_thi_theo_loai(string loai) const;
    int tim_xe(int ma_xe) const;
    
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), tong_xe(0) {}

bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), tong_xe(0) {}

int bai_xe::lay_ma() const { return ma_bai; }

bool bai_xe::them(phuong_tien v) {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    if (cap >= 1 && tong_xe==0) { pt[0] = v; tong_xe++; return true; }
    if (cap >= 2 && tong_xe==1) { pt[1] = v; tong_xe++; return true; }
    if (cap >= 3 && tong_xe==2) { pt[2] = v; tong_xe++; return true; }
    return false;
}

bool bai_xe::xoa(int ma_xe) {
    if (tong_xe>=1 && pt[0].lay_ma_xe() == ma_xe) {
        if (tong_xe>=2) {
            pt[0] = pt[1];
            if (tong_xe>=3) { pt[1] = pt[2]; }
        }
		tong_xe--;
        return true;
    }
    if (tong_xe>=2 && pt[1].lay_ma_xe() == ma_xe) {
        if (tong_xe>=3) { pt[1] = pt[2]; }
        tong_xe--;
        return true;
    }
    if (tong_xe>=3 && pt[2].lay_ma_xe() == ma_xe) {
        tong_xe--;
        return true;
    }
    return false;
}

bool bai_xe::chua(int ma_xe) const {
    if (tong_xe>=1 && pt[0].lay_ma_xe() == ma_xe) return true;
    if (tong_xe>=2 && pt[1].lay_ma_xe() == ma_xe) return true;
    if (tong_xe>=3 && pt[2].lay_ma_xe() == ma_xe) return true;
    return false;
}

bool bai_xe::da_day() const{
	int suc_chua = (kich_thuoc=='S') ? 1 : (kich_thuoc=='M') ? 2 :3;
	if (suc_chua<so_xe) return false;
	return true;
}

void bai_xe::hien_thi() const {
	int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << tong_xe << "/" << cap << " xe\n";
    for (int i=0; i<tong_xe; i++){
    	pt[i].hien_thi();
	}
}
void bai_xe::hien_thi_theo_loai(string loai) const {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    int so_xe = (pt[0].lay_loai_xe()==loai) + (pt[1].lay_loai_xe()==loai) + (pt[2].lay_loai_xe()==loai);
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_xe << "/" << cap << " xe\n";
    if (tong_xe>=1 && pt[0].lay_loai_xe()==loai) pt[0].hien_thi();
    if (tong_xe>=2 && pt[1].lay_loai_xe()==loai) pt[1].hien_thi();
    if (tong_xe>=3 && pt[2].lay_loai_xe()==loai) pt[2].hien_thi();
}

bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0; tong = 0;
    if (tong_xe>=1 && pt[0].lay_loai_xe() == loai) { ++dem; tong += pt[0].tinh_phi(); }
    if (tong_xe>=2 && pt[1].lay_loai_xe() == loai) { ++dem; tong += pt[1].tinh_phi(); }
    if (tong_xe>=3 && pt[2].lay_loai_xe() == loai) { ++dem; tong += pt[2].tinh_phi(); }
    return dem > 0;
}

int bai_xe::tim_xe(int ma_xe) const {
	if (tong_xe>=1 && pt[0].lay_ma_xe()==ma_xe) { return 0; }
	if (tong_xe>=2 && pt[1].lay_ma_xe()==ma_xe) { return 1; }
	if (tong_xe>=3 && pt[2].lay_ma_xe()==ma_xe) { return 2; }
	return -1;
} 

class SystemInterface {
private:
    bai_xe bai1, bai2, bai3;   // sau này dùng m?ng
    bool co1, co2, co3;

public:
    SystemInterface();
    void runMenu();
};

SystemInterface::SystemInterface() : co1(false), co2(false), co3(false) {}

void SystemInterface::runMenu() {
    int chon;
    while (chon!=9) {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon: ";
        cin >> chon;
        switch(chon){
        case 1:{
            int ma; char kt;
            cout << "Ma bai: "; cin >> ma;
            cout << "Kich thuoc (S/M/L): "; cin >> kt;
            if (co1 && co2 && co3){\
				cout << "Khong the them bai";
				break;
			}
            if (!co1)      { bai1 = bai_xe(ma, kt); co1 = true; }
            else if (!co2) { bai2 = bai_xe(ma, kt); co2 = true; }
            else if (!co3) { bai3 = bai_xe(ma, kt); co3 = true; }
			else cout << "Da tao bai " << ma << "\n";
            break;
		}
        case 2: {
            int ma, gio, tg; 
			string loai;
            cout << "Ma xe: "; cin >> ma;
            cout << "Loai (Car/Motorcycle/Bicycle): "; cin >> loai;
            cout << "Gio vao (0-23): "; cin >> gio;
            cout << "Thoi luong (1-23): "; cin >> tg;
            phuong_tien v(ma, loai, gio, tg);
            bool ok = false;
            if (co1 && !ok) ok = bai1.them(v);
            if (co2 && !ok) ok = bai2.them(v);
            if (co3 && !ok) ok = bai3.them(v);
            if (ok) cout << "Da them xe " << ma << " | Phi: $" << fixed << setprecision(2) << v.tinh_phi() << "\n";
            else    cout << "Tat ca bai da day!\n";
            break;
		}
        case 3: {
            int ma;
            cout << "Ma bai can xoa: "; cin >> ma;
            if (co1 && bai1.lay_ma() == ma) {
                if (co2) { bai1 = bai2; if (co3) { bai2 = bai3; co3 = false; } else co2 = false; }
                else co1 = false;
                cout << "Da xoa bai " << ma << "\n";
            }
            else if (co2 && bai2.lay_ma() == ma) {
                if (co3) { bai2 = bai3; co3 = false; } else co2 = false;
                cout << "Da xoa bai " << ma << "\n";
            }
            else if (co3 && bai3.lay_ma() == ma) {
                co3 = false;
                cout << "Da xoa bai " << ma << "\n";
            }
        	break;
		}
        case 4:{
            int ma;
            cout << "Ma xe can lay ra: "; cin >> ma;
            bool ok = false;
            if (co1 && !ok) ok = bai1.xoa(ma);
            if (co2 && !ok) ok = bai2.xoa(ma);
            if (co3 && !ok) ok = bai3.xoa(ma);
            cout << (ok ? "Da lay xe ra\n" : "Khong tim thay xe\n");
        	break;
		}
        case 5:{
            if (co1) bai1.hien_thi();
            if (co2) bai2.hien_thi();
            if (co3) bai3.hien_thi();
        	break;
		}
        case 6:{
            int ma;
            cout << "Ma bai: "; cin >> ma;
            if (co1 && bai1.lay_ma() == ma) bai1.hien_thi();
            else if (co2 && bai2.lay_ma() == ma) bai2.hien_thi();
            else if (co3 && bai3.lay_ma() == ma) bai3.hien_thi();
        	break;
		}
        case 7:{
            string loai;
            cout << "Loai xe: "; cin >> loai;
            int dem; double tong;
            if (co1 && bai1.co_loai(loai, dem, tong)) bai1.hien_thi_theo_loai(loai);
            if (co2 && bai2.co_loai(loai, dem, tong)) bai2.hien_thi_theo_loai(loai);
            if (co3 && bai3.co_loai(loai, dem, tong)) bai3.hien_thi_theo_loai(loai);
        	break;
		}
        case 8:{
            string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};
            for (int t = 0; t < 3; ++t) {
                int dem = 0; double tong = 0;
                int d; double s;
                if (co1) { bai1.co_loai(loai_arr[t], d, s); dem += d; tong += s; }
                if (co2) { bai2.co_loai(loai_arr[t], d, s); dem += d; tong += s; }
                if (co3) { bai3.co_loai(loai_arr[t], d, s); dem += d; tong += s; }
                cout << loai_arr[t] << ": ";
                if (dem == 0) cout << "khong co xe\n";
                else cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
            }
        	break;
		}
        case 9:
			break;
		default: break;
		}
    }
}

int main() {
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
