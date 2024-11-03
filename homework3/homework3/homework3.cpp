// homework3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <list>
#include <forward_list>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

using namespace std;

// 圖書資訊結構
struct Book {
    string title;  // 書名
    string author; // 作者
    string id;     // 圖書編號

    // 建構函式
    Book(string t, string a, string i) : title(t), author(a), id(i) {}
};

// 借閱者資訊結構
struct Borrower {
    string name;                   // 姓名
    vector<string> borrowedBooks;  // 借閱的圖書編號列表

    // 建構函式
    Borrower(string n, vector<string> b) : name(n), borrowedBooks(b) {}
};

// 驗證圖書編號格式的函式
bool isValidBookId(const string& id) {
    regex pattern("^[A-Za-z][0-9]{4}$"); // 定義正則表達式，要求首字母是英文字母，後面是4位數字
    return regex_match(id, pattern);      // 檢查圖書編號是否符合格式
}

class Library {
private:
    list<Book> books;                     // 使用 std::list 管理圖書資訊
    forward_list<Borrower> borrowers;     // 使用 std::forward_list 管理借閱者資訊

public:
    // 添加新圖書的函式
    void addBook(const string& title, const string& author, const string& id) {
        if (isValidBookId(id)) { // 驗證圖書編號
            books.emplace_back(title, author, id); // 添加新圖書
            cout << "圖書添加成功: " << title << endl;
        }
        else {
            cout << "圖書編號格式不正確，請重新輸入。" << endl;
        }
    }

    // 刪除指定圖書編號的圖書
    void removeBook(const string& id) {
        // 查找圖書編號
        auto it = find_if(books.begin(), books.end(), [&id](const Book& book) { return book.id == id; });
        if (it != books.end()) {
            books.erase(it); // 刪除圖書
            cout << "圖書刪除成功: " << id << endl;
        }
        else {
            cout << "未找到該圖書編號。" << endl;
        }
    }

    // 搜索指定圖書編號的圖書
    void searchBook(const string& id) {
        auto it = find_if(books.begin(), books.end(), [&id](const Book& book) { return book.id == id; });
        if (it != books.end()) {
            cout << "找到圖書: " << it->title << "，作者: " << it->author << endl; // 輸出找到的圖書資訊
        }
        else {
            cout << "未找到該圖書編號。" << endl;
        }
    }

    // 按圖書編號排序列出所有圖書
    void listBooks() {
        books.sort([](const Book& a, const Book& b) { return a.id < b.id; }); // 按照圖書編號排序
        for (const auto& book : books) {
            cout << "書名: " << book.title << ", 作者: " << book.author << ", 編號: " << book.id << endl;
        }
    }

    // 添加新借閱者
    void addBorrower(const string& name, const vector<string>& borrowedBooks) {
        borrowers.emplace_front(name, borrowedBooks); // 添加新借閱者
        cout << "借閱者添加成功: " << name << endl;
    }

    // 刪除指定姓名的借閱者
    void removeBorrower(const string& name) {
        borrowers.remove_if([&name](const Borrower& borrower) { return borrower.name == name; }); // 根據姓名刪除借閱者
        cout << "借閱者刪除成功: " << name << endl;
    }

    // 搜索指定姓名的借閱者
    void searchBorrower(const string& name) {
        for (const auto& borrower : borrowers) {
            if (borrower.name == name) {
                cout << "找到借閱者: " << borrower.name << ", 借閱的圖書編號: ";
                for (const auto& bookId : borrower.borrowedBooks) {
                    cout << bookId << " "; // 列出借閱的圖書編號
                }
                cout << endl;
                return;
            }
        }
        cout << "未找到該借閱者。" << endl;
    }

    // 列出所有借閱者及其借閱的圖書
    void listBorrowers() {
        for (const auto& borrower : borrowers) {
            cout << "借閱者: " << borrower.name << ", 借閱的圖書編號: ";
            for (const auto& bookId : borrower.borrowedBooks) {
                cout << bookId << " "; // 列出借閱的圖書編號
            }
            cout << endl;
        }
    }
};

int main() {
    Library library;

    // 測試資料：添加圖書
    library.addBook("紅樓夢", "曹雪芹", "A1234");
    library.addBook("西遊記", "吳承恩", "B2345");
    library.addBook("水滸傳", "施耐庵", "B3456");
    library.addBook("三國演義", "羅貫中", "C4567");
    library.addBook("金瓶梅", "蘭陵笑笑生", "C5678");
    library.addBook("聊齋志異", "蒲松齡", "D6789");
    library.addBook("儒林外史", "吳敬梓", "D7890");
    library.addBook("封神演義", "許仲琳", "E8901");
    library.addBook("鏡花緣", "李汝珍", "E9012");
    library.addBook("老殘遊記", "劉鶚", "F0123");

    // 測試資料：添加借閱者
    library.addBorrower("小明", { "A1234", "B2345" });
    library.addBorrower("小華", { "C4567" });
    library.addBorrower("小美", { "D6789", "E8901" });
    library.addBorrower("小強", { "F0123" });
    library.addBorrower("小麗", { "B3456", "C5678" });

    // 測試功能：列出圖書和借閱者
    library.listBooks();
    library.listBorrowers();

    // 測試搜索功能
    library.searchBook("A1234");
    library.searchBorrower("小明");

    // 測試刪除功能
    library.removeBook("B2345");
    library.removeBorrower("小華");

    // 最終列出圖書和借閱者
    library.listBooks();
    library.listBorrowers();

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
