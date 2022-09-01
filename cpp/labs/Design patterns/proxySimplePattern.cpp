// ProxyPatternSample.cpp 
 /*
Task:
    create a Box class and restrict the access through Authentication
 */
#include <iostream>
using namespace std;

class IBox
{
public:
    virtual void Open() = 0;
    virtual ~IBox() {};
};
 
class SimpleBox : public IBox
{
public:
    virtual void Open()
    {
        cout << "Opening te box";
    }
};
 
 
class ProxyBox : public IBox
{
public:
    ProxyBox(string sUserName, string sPwd):m_UserName(), m_Pwd(sPwd)
    {
 
    }
 
    void Open()
    {
        if (iSAuthenticated()) {
            cout << "\nAuthentication Success";
            m_Box.Open();
            cout << "Open is called" ;
        }
        else
            cout << "\nAuthentication Failure , You can't open the Box";
    }
private:
    bool iSAuthenticated()
    {
        bool bAuthenticated = false;
        //bAuthenticated = AUthenication logic here
        return bAuthenticated;
 
    }
private:
    string m_UserName;
    string m_Pwd;
    SimpleBox m_Box;
};
 
int main()
{
    IBox* box = new ProxyBox("Admin", "Test123");
    box->Open();
    delete box;
}