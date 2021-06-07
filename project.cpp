#include <iostream>
#include <list>
#include <stdlib.h>
#include <unistd.h>
#include<string> 
#include<setjmp.h>
jmp_buf buf;

using namespace std;
int mat=0,ser=0,me=0,se=0,l;
string M[100],S[100],orgn;

// Αναπαριστά ένα χρήστη 
class User {
    public:
        string name;
        int phone;     
};
//Aντιπροσωπεύει ένα είδος δωρεάς

 class Entity {
    public:
       string name; // το όνομα του προιόντος
       string description; // περιγραφή προιόντος
       int id; // κωδικός του είδους
    public: 
        
        string getEntityInfo(){// επιστρέφει τις προηγούμενες πληροφορίες προιόντος.
            return name + description + to_string(id) ;
            
        }
         virtual string getDetails(){ return 0;}
        const string toString() {
           return  getEntityInfo() +""+ getDetails();
          
        }
}; 
//Ποσότητες που δικαιούνται


class Material : public Entity{
    public:
        //που αντιπροσωπεύουν τρία επίπεδα ποσοτήτων που μπορεί να δικαιούται κάποιος από ένα material.
        double level1;//είναι η ποσότητα που δικαιούται 1 άτομο
        double level2;//είναι η ποσότητα που δικαιούται 2-4 άτομα
        double level3;//είναι η ποσότητα που δικαιούται >=5 άτομα  
    public:
        
        Material(string n,string d,int x,double l1,double l2,double l3){
            M[me]=n;
            me=me+1;
            mat=mat+1;
            name=n;
            description=d;
            id=x;  
            level1=l1;
            level2=l2;
            level3=l3;
        }
        string getDetails(){//η οποία επιστρέφει τις επιπλέον πληροφορίες για τα αντικείμενα Material (τα levels και το ότι το αντικείμενο είναι Material)
           return  "This Entity is Material";
            
        }
};

//Αναπαριστά Services.

class Service : public Entity{
    public:
   
        Service(string n,string d,int x){
             S[se]=n;
             se=se+1;
            ser=ser+1;
            name=n;
            description=d;
            id=x;
        }
        string getDetails(){//και επιστρέφει ως επιπλέον πληροφορία ότι το αντικείμενο είναι Service
            return "This Entity is Service";
            
        }
};

//Αναπαριστά ένα χρήστη που είναι ο διαχειριστής του συστήματος.
class Beneficiary : public User{
    public:
        int noPersons = 1;//το οποίο δηλώνει πόσα άτομα έχει η οικογένεια του
        //RequestDonationList receivedList; //αναπαριστά τη λίστα των ειδών και των ποσοτήτων που έχει ήδη λάβει.
        //Requests requestsList; //αναπαριστά την τρέχουσα λίστα των ειδών και των ποσοτήτων που ζητά να του δοθούν.
    public:
        Beneficiary(string n , int p ,int num){
            name=n;
            phone=p;
            noPersons=num;
        }
}; 
class Donator : public User{
    public:
       // Offers offerList;//το οποίο αναπαριστά τη λίστα ειδών που επιθυμεί να προσφέρει.
    public:
        Donator(string n , int p ){
            name=n;
            phone=p;
        }
};
class Admin : public User{
    public:
        bool isAdmin = true;
    public:
        
};
//Αντιστοιχεί στον οργανισμό που υποστηρίζει το σύστημα donation.

class Organization{
   public:
        string name,an,reminder;
        int p;
        list<Entity> entityList;//μια λίστα entityList με τα είδη (entity) που μπορούν να διανεμηθούν σε Beneficiaries
        list<Donator> donatorList; //μια λίστα donators
        list<Beneficiary> beneficiaryList;//μια λίστα beneficiaries
        list<Material> mList;
        list<Service> sList;
        //RequestDonationList currentDonations;
    private:
        
        Admin admin;
        
        //RequestDonationList currentDonations;//με τις διαθέσιμες προσφορές και τις ποσότητές τους.
    public:
        friend class Menu;
        Organization(string n){
            name=n;   
        }
        void setAdmin(){
        getline(cin,reminder);
         cout << "Admin name: ";
         getline(cin,an);
         admin.name=an;
         cout << "Admin phone: ";
         cin >> p ;
         getline(cin,reminder);
         admin.phone=p;
         cout << admin.phone;
        }//για την καταχώρηση και την ανάκτηση του Admin του οργανισμού, αντίστοιχα.
        Admin getAdmin(){
            return admin;
        }
      
        void addEntity(Entity e)
       {
          entityList.push_back(e); 
                
        }//προσθέτει ένα νέο είδος (entity) που μπορεί να διακινηθεί από τον οργανισμό. Γίνεται χειρισμός εξαίρεσης αν υπάρχει ήδη.
         void addMaterial(Material e)
       {
          mList.push_back(e); 
                
        }
         void addService(Service e)
       {
          sList.push_back(e); 
                
        }
         
 
 
         /* void removeEntity(Entity e){
           
            for(list<Entity>::iterator it = entityList.begin(); it!= entityList.end(); ++it)
  { 
                    Entity item = *it;
                    if (item.name==e.name){
                        entityList.remove(item); 
                    }
                    
  } 
         } */
         //διαγράφεται ένα Entity όταν παύει να διακινείται από τον οργανισμό. Τη διαγραφή την κάνει μόνο ο Admin.
 
        void insertDonator(Donator p){
            donatorList.push_back(p); 
        }//προσθέτει έναν Donator στον οργανισμό. Γίνεται χειρισμός εξαίρεσης, αν υπάρχει ήδη.
      // void removeDonator(Donator e){
         
        
      //  }//αφαιρεί έναν Donator από τον οργανισμό.

        void insertBeneficiary(Beneficiary p){
           
            beneficiaryList.push_back(p); 
        };//προσθέτει έναν Beneficiary στον οργανισμό. Γίνεται χειρισμός εξαίρεσης, αν υπάρχει ήδη.
       // removeBeneficiary (){
           
       // };//αφαιρεί έναν Beneficiary  //από τον οργανισμό

         void listEntities(){
           for(list<Entity>::iterator it = entityList.begin(); it!= entityList.end(); ++it)
  { 
                    Entity item = *it;
                    cout << item.name + item.description + to_string(item.id)<<"\n";
  }
        } //Εμφανίζει τις υπάρχουσες κατηγορίες των entity (material, services) και λίστα με όλα τα entity ανά συγκεκριμένη κατηγορία.
        void listBeneficiaries(){
                int i=1;
             for(list<Beneficiary>::iterator it = beneficiaryList.begin(); it!= beneficiaryList.end(); ++it)
  {                 
                    Beneficiary item = *it;
                    
                    cout <<i<<"] "<< item.name<<"\n"; //+ to_string(item.phone) + to_string(item.noPersons)
                    i++;
                   
  }
        }//εμφανίζει τους επωφελούμενους Beneficiaries και την τρέχουσα κατάσταση παροχών που έχουν λάβει ανά είδος.
      void listDonators(){
            for(list<Donator>::iterator it = donatorList.begin(); it!= donatorList.end(); ++it)
  { 
                    Donator item = *it;
                    cout << item.name + to_string(item.phone) <<"\n";
  }
        }//εμφανίζει τους δωρητές Donators.
        //Προαιρετικά, wrapper μεθόδους για μεθόδους του αντικειμένου currentDonations
};
//Απεικονίζει το αίτημα ή την παροχή για ένα συγκεκριμένο Entity σε συγκεκριμένη ποσότητα quantity.
class RequestDonation {
    public:
        Entity entity;
        double quantity;
    public:
        RequestDonation(Entity nEn,double q){
            entity.name=nEn.name;
            entity.description=nEn.description;
            entity.id=nEn.id;
            quantity=q;
        }
};
//Αναπαριστά μια συλλογή από αντικείμενα RequestDonation και δίνει μεθόδους για την ενημέρωση της λίστας αυτής1
class RequestDonationList{
    private:
        list<RequestDonation> rdEntities;
    public:
        RequestDonation get(int id){
           for(list<RequestDonation>::iterator it = rdEntities.begin(); it!= rdEntities.end(); ++it)
         { 
                    RequestDonation item = *it;
                     if(item.entity.id==id){
                         return item;
                     }                 
         }
        }//Επιστρέφει ένα συγκεκριμένο RequestDonation από τη συλλογή, δίνοντας το id του Entity.
        virtual void add(RequestDonation RD,Organization org){
            for(list<Entity>::iterator it = org.entityList.begin(); it!= org.entityList.end(); ++it)
         {          Entity item=*it;
                   if(RD.entity.id!=item.id)
                        cout <<"Error Item dont exist in Organization."<<endl;
                        break;
         }
            for(list<RequestDonation>::iterator it = rdEntities.begin(); it!= rdEntities.end(); ++it)
         { 
                    RequestDonation item = *it;
                     if(item.entity.id==RD.entity.id){
                        item.quantity=item.quantity+RD.quantity;
                     }    
                     else if (item.entity.id!=RD.entity.id)   {
                         RequestDonation newRD( RD.entity,RD.quantity);
                         rdEntities.push_back(newRD);
                     }  
         }  
        }//Μέθοδος η οποία τοποθετεί ένα συγκεκριμένο requestDonation στην rdEntities. Αν το requestDonation αφορά entity που ήδη υπάρχει σε κάποιο requestDonation της συλλογής, γίνεται ενημέρωση της ποσότητας του υπάρχοντος. Αν αφορά entity που δεν υπάρχει σε κάποιο requestDonation, δημιουργεί νέο αντικείμενο και το προσθέτει στη συλλογή. Αν αφορά entity που δεν υπάρχει στην entityList του οργανισμού, εγείρεται εξαίρεση.
        /* void remove(RequestDonation RD){
                 for(list<RequestDonation>::iterator it = rdEntities.begin(); it!= rdEntities.end(); ++it)
         { 
                    RequestDonation item = *it;
                     if(item.entity.id==RD.entity.id){
                        rdEntities.delete(item);
                     }    
         }   */

        // Αφαιρεί ένα RequestDonation από την rdEntities.
         void modify(RequestDonation RD){
                 double nquantity;
                  for(list<RequestDonation>::iterator it = rdEntities.begin(); it!= rdEntities.end(); ++it)
         { 
                    RequestDonation item = *it;
                     if(item.entity.id==RD.entity.id){
                        cout<<"Change quantity of "<< item.entity.name << "from " << item.quantity << "to: ";
                        cin >> nquantity;
                        item.quantity=nquantity;
                     }    
         }  
        }// Για ένα αντικείμενο στη συλλογή τροποποιεί το quantity.
       void monitor(){
            for(list<RequestDonation>::iterator it = rdEntities.begin(); it!= rdEntities.end(); ++it)
        { 
                    RequestDonation item = *it;
                    cout <<"Entity name: "<< item.entity.name <<"\n"<<"Quantity: " << item.quantity<<endl ;
        }
        }// Εμφανίζει το σύνολο των ειδών που βρίσκεται στη λίστα rdEntities, δηλαδή τα ονόματα των entity και τις ποσότητες που τους αντιστοιχούν.
        void reset(){
            rdEntities.clear();
        }// Aφαιρεί όλα τα αντικείμενα από τη λίστα
};

//Αναπαριστά το σύνολο των ειδών (Material ή Services) που ζητά ο Beneficiary
class Requests : public RequestDonationList{
    public:
        void Check(RequestDonation RD,Organization org){
           /*  for(list<RequestDonationList>::iterator it = org.currentDonations.begin(); it!= org.currentDonations.end(); ++it)
         {          RequestDonationList item=*it;
                   for(list<RequestDonation>::iterator it = RequestDonationList::rdEntities.begin(); it!= RequestDonationList::rdEntities.end(); ++it)
         {          RequestDonation item=*it;
                    if(item.entity.id==RD.entity.id)
                        if(item.quantity>=RD.quantity)       
         }
         } */

        }
        void modify(){};
        void validRequestDonation(){ };
        void commit(){};
};
//Αναπαριστά το σύνολο των ειδών που προτίθεται να συνεισφέρει ο Donator
class Offers: public RequestDonationList{
    public:
      void commit(){};
        //Ενημερώνει τα currentDonations του οργανισμού με τις προσφορές που περιέχονται 
        //στη λίστα rdEntities. Αν αυτό ολοκληρωθεί επιτυχώς, διαγράφει τα περιεχόμενα της λίστας rdEntities.
};


//αναπαριστά το μενού της εφαρμογής και περιλαμβάνει μεθόδους για την εκτύπωση των επιλογών, τον χειρισμό της εισόδου του χρήστη και την πλοήγηση στο μενού.
class Menu  {
    private:
        int f=0;
    public:
        void menuAdmin(Admin a,Organization b){
           while(true){
            int mchoice,number=0;
            char schooce;
            system("CLS");
            sleep(0.1);
            cout << "Welcome Admin "<< a.name<< endl ;
            cout <<"----------------------------"<<endl;
            cout << "Info:"<<endl;
            cout << "Name:"<<a.name<<endl;
            cout << "Phone:"<<a.phone<<endl;
            cout << "Admin:"<<a.isAdmin << " [Comfirmed] "<<endl;
            cout <<"----------------------------"<<endl;
            cout << "Choose Page:"<<endl;
            cout << "1]View Materials & Services"<<endl;
            cout << "2]Monitor Organization"<<endl;
            cout << "\n->";
            cin >> mchoice;
            if (mchoice==1){
                while(true){
                int kchoice;
            system("CLS");
            sleep(0.1);
            cout << "Categories:"<<endl;
            cout << "1]Materials ~ " << mat << endl;
            cout << "2]Services ~ " << ser <<endl;
            cout << "3]BACK" <<endl;
            cout << "4]Logout" <<endl;
            cout << "5]Exit" <<endl;
            cout << "Choose:";
            cin >> kchoice;
            if (kchoice==1)
            {   while(true){
               system("CLS");
                 sleep(0.1);
                 cout << "Materials: " << endl; 
                 cout <<"----------------------------"<<endl;
                 char i ='a';
                  for(list<Material>::iterator it = b.mList.begin(); it!= b.mList.end(); ++it)
                { 
                    Material item = *it;
                    number=int(i);
                    cout << i <<"]" << item.name <<"\n";
                    number++;
                    i=char(number);
                 }
                cout <<"----------------------------"<<endl;
                cout << "x]BACK" <<endl;
                cout << "y]Logout" <<endl;
                cout << "z]Exit" <<endl;
                cout <<"----------------------------"<<endl;
                cout << "Choose:";
                cin >> schooce;
                if (schooce=='x'){
                    break;
                }
                else if(schooce=='z'){
                    exit (EXIT_SUCCESS);
                }
                else if(schooce=='y'){
                    longjmp(buf, 1);
                }
                system("CLS");
                sleep(0.1);
                char k ='a';
                while(true){
               for(list<Material>::iterator it = b.mList.begin(); it!= b.mList.end(); ++it)
                {   
                    Material item = *it;
                    if(k==schooce){
                     cout <<"Details:"<<endl;
                     cout <<"----------------------------"<<endl;
                     cout <<"Name:        "<< item.name<<endl;
                     cout <<"Description: "<< item.description<<endl;
                     cout <<"ID:          "<< to_string(item.id)<<endl;
                     cout <<"Level1:      "<< to_string(item.level1) <<endl;
                     cout <<"Level2:      "<< to_string(item.level2) <<endl;
                     cout <<"Level3:      "<< to_string(item.level3) <<endl;
                     cout <<"----------------------------"<<endl;
                    }
                    number=int(k);
                    number++;
                    k=char(number);
                 }
                cout <<"----------------------------"<<endl;
                cout << "x]BACK" <<endl;
                cout << "y]Logout" <<endl;
                cout << "z]Exit" <<endl;
                cout <<"----------------------------"<<endl;
                cout << "Choose:";
                cin >> schooce;
                if (schooce=='x'){
                    break;
                }
                else if(schooce=='z'){
                    exit (EXIT_SUCCESS);
                }
                else if(schooce=='y'){
                    longjmp(buf, 1);
                }
                system("CLS");
                sleep(0.1);
                }
            }
                
            }
            else if (kchoice==2)
            {  while(true){
               system("CLS");
                 sleep(0.1);
                 cout << "Services: " << endl; 
                 cout <<"----------------------------"<<endl;
                 char i ='a';
                  for(list<Service>::iterator it = b.sList.begin(); it!= b.sList.end(); ++it)
                { 
                    Service item = *it;
                    number=int(i);
                    cout << i <<"]" << item.name <<"\n";
                    number++;
                    i=char(number);
                 }
                cout <<"----------------------------"<<endl;
                cout << "x]BACK" <<endl;
                cout << "y]Logout" <<endl;
                cout << "z]Exit" <<endl;
                cout <<"----------------------------"<<endl;
                cout << "Choose:";
                cin >> schooce;
                if (schooce=='x'){
                    break;
                }
                else if(schooce=='z'){
                    exit (EXIT_SUCCESS);
                }
                else if(schooce=='y'){
                    longjmp(buf, 1);
                }
                system("CLS");
                sleep(0.1);
                char k ='a';
                while(true){
               for(list<Service>::iterator it = b.sList.begin(); it!= b.sList.end(); ++it)
                {   
                    Service item = *it;
                    if(k==schooce){
                     cout <<"Details:"<<endl;
                     cout <<"----------------------------"<<endl;
                     cout <<"Name:        "<< item.name<<endl;
                     cout <<"Description: "<< item.description<<endl;
                     cout <<"ID:          "<< to_string(item.id)<<endl;
                     cout <<"----------------------------"<<endl;
                    }
                    
                    number=int(k);
                    number++;
                    k=char(number);
                     
                 }
                cout <<"----------------------------"<<endl;
                cout << "x]BACK" <<endl;
                cout << "y]Logout" <<endl;
                cout << "z]Exit" <<endl;
                cout <<"----------------------------"<<endl;
                cout << "Choose:";
                cin >> schooce;
                if (schooce=='x'){
                    break;
                }
                else if(schooce=='z'){
                    exit (EXIT_SUCCESS);
                }
                else if(schooce=='y'){
                    longjmp(buf, 1);
                }
                system("CLS");
                sleep(0.1);
                }
            }
      }
                
      else if(kchoice==5){

          exit (EXIT_SUCCESS);
      }
      else if(kchoice==3){
          break;
      }
      else if(kchoice==4){
          longjmp(buf, 1);
      }
            }
        }
        else if(mchoice==2){
            while(true){
            system("CLS");
            sleep(0.1);
            cout <<"Beneficiary List:"<<endl;
            cout <<"----------------------------"<<endl;
            b.listBeneficiaries();
            cout <<"----------------------------"<<endl;
                cout << "x]BACK" <<endl;
                cout << "y]Logout" <<endl;
                cout << "z]Exit" <<endl;
                cout <<"----------------------------"<<endl;
                cout << "Choose:";
                cin >> schooce;
                if (schooce=='x'){
                    break;
                }
                else if(schooce=='z'){
                    exit (EXIT_SUCCESS);
                }
                else if(schooce=='y'){
                    longjmp(buf, 1);
                }
            }
        }



           } //end while arxikis 
    } //end menuadmin
    
        void menuBeneficiary(Beneficiary a,Organization b){
            while(true){
            int kchooce;
            system("CLS");
            sleep(0.1);
            cout << "Welcome Beneficiary "<< a.name<< endl ;
            cout << "\n";
            cout << "Info:"<<endl;
            cout << "Name:"<<a.name<<endl;
            cout << "Phone:"<<a.phone<<endl;
            cout << "Family members:"<<a.noPersons<<endl;
            cout << "Organization:"<<orgn<<endl;
            cout << "Name of Headmember:"<<a.name<<endl;
            cout << "\n";
            cout << "Choose Page:"<<endl;
            cout << "1]Add Request"<<endl;
            cout << "2]Show Requests:"<<endl;
            cout << "3]Commit:"<<endl;
            cout << "4]BACK" <<endl;
            cout << "5]Logout" <<endl;
            cout << "6]Exit" <<endl;
            cout << "Choose:";
            cin >> kchooce;
            if (kchooce==4){
                    longjmp(buf, 1);
                }
                else if(kchooce==6){
                    exit (EXIT_SUCCESS);
                }
                else if(kchooce==5){
                    longjmp(buf, 1);
                }
            }
        }
        void menuDonator(Donator a,Organization b){
            int mchoice,number,schooce;
             while(true){
            
            system("CLS");
            sleep(0.1);
            cout << "Welcome Donator "<< a.name<< endl ;
            cout << "\n";
            cout << "Info:"<<endl;
            cout << "Name:"<<a.name<<endl;
            cout << "Phone:"<<a.phone<<endl;
            cout << "Organization:"<<orgn<<endl;
            cout << "Name of Headmember:"<<a.name<<endl;
            cout << "\n";
            cout << "Choose Page:"<<endl;
            cout << "1]Add Offer"<<endl;
            cout << "2]Show Offers"<<endl;
            cout << "3]Commit"<<endl;
            cout << "\n->";
            cin >> mchoice;
          if (mchoice==1){
                while(true){
                int kchoice;
            system("CLS");
            sleep(0.1);
            cout << "Categories:"<<endl;
            cout << "1]Materials ~ " << mat << endl;
            cout << "2]Services ~ " << ser <<endl;
            cout << "3]BACK" <<endl;
            cout << "4]Logout" <<endl;
            cout << "5]Exit" <<endl;
            cout << "Choose:";
            cin >> kchoice;
            if (kchoice==1)
            {   while(true){
               system("CLS");
                 sleep(0.1);
                 cout << "Materials: " << endl; 
                 cout <<"----------------------------"<<endl;
                 char i ='a';
                  for(list<Material>::iterator it = b.mList.begin(); it!= b.mList.end(); ++it)
                { 
                    Material item = *it;
                    number=int(i);
                    cout << i <<"]" << item.name <<"\n";
                    number++;
                    i=char(number);
                 }
                cout <<"----------------------------"<<endl;
                cout << "x]BACK" <<endl;
                cout << "y]Logout" <<endl;
                cout << "z]Exit" <<endl;
                cout <<"----------------------------"<<endl;
                cout << "Choose:";
                cin >> schooce;
                if (schooce=='x'){
                    break;
                }
                else if(schooce=='z'){
                    exit (EXIT_SUCCESS);
                }
                else if(schooce=='y'){
                    longjmp(buf, 1);
                }
                system("CLS");
                sleep(0.1);
                char k ='a';
                while(true){
               for(list<Material>::iterator it = b.mList.begin(); it!= b.mList.end(); ++it)
                {   
                    Material item = *it;
                    if(k==schooce){
                     cout <<"Details:"<<endl;
                     cout <<"----------------------------"<<endl;
                     cout <<"Name:        "<< item.name<<endl;
                     cout <<"Description: "<< item.description<<endl;
                     cout <<"ID:          "<< to_string(item.id)<<endl;
                     cout <<"Level1:      "<< to_string(item.level1) <<endl;
                     cout <<"Level2:      "<< to_string(item.level2) <<endl;
                     cout <<"Level3:      "<< to_string(item.level3) <<endl;
                     cout <<"----------------------------"<<endl;
                    }
                    number=int(k);
                    number++;
                    k=char(number);
                 }
                cout <<"----------------------------"<<endl;
                cout << "x]BACK" <<endl;
                cout << "y]Logout" <<endl;
                cout << "z]Exit" <<endl;
                cout <<"----------------------------"<<endl;
                cout << "Choose:";
                cin >> schooce;
                if (schooce=='x'){
                    break;
                }
                else if(schooce=='z'){
                    exit (EXIT_SUCCESS);
                }
                else if(schooce=='y'){
                    longjmp(buf, 1);
                }
                system("CLS");
                sleep(0.1);
                }
            }
                
            }
            else if (kchoice==2)
            {  while(true){
               system("CLS");
                 sleep(0.1);
                 cout << "Services: " << endl; 
                 cout <<"----------------------------"<<endl;
                 char i ='a';
                  for(list<Service>::iterator it = b.sList.begin(); it!= b.sList.end(); ++it)
                { 
                    Service item = *it;
                    number=int(i);
                    cout << i <<"]" << item.name <<"\n";
                    number++;
                    i=char(number);
                 }
                cout <<"----------------------------"<<endl;
                cout << "x]BACK" <<endl;
                cout << "y]Logout" <<endl;
                cout << "z]Exit" <<endl;
                cout <<"----------------------------"<<endl;
                cout << "Choose:";
                cin >> schooce;
                if (schooce=='x'){
                    break;
                }
                else if(schooce=='z'){
                    exit (EXIT_SUCCESS);
                }
                else if(schooce=='y'){
                    longjmp(buf, 1);
                }
                system("CLS");
                sleep(0.1);
                char k ='a';
                while(true){
               for(list<Service>::iterator it = b.sList.begin(); it!= b.sList.end(); ++it)
                {   
                    Service item = *it;
                    if(k==schooce){
                     cout <<"Details:"<<endl;
                     cout <<"----------------------------"<<endl;
                     cout <<"Name:        "<< item.name<<endl;
                     cout <<"Description: "<< item.description<<endl;
                     cout <<"ID:          "<< to_string(item.id)<<endl;
                     cout <<"----------------------------"<<endl;
                    }
                    
                    number=int(k);
                    number++;
                    k=char(number);
                     
                 }
                cout <<"----------------------------"<<endl;
                cout << "x]BACK" <<endl;
                cout << "y]Logout" <<endl;
                cout << "z]Exit" <<endl;
                cout <<"----------------------------"<<endl;
                cout << "Choose:";
                cin >> schooce;
                if (schooce=='x'){
                    break;
                }
                else if(schooce=='z'){
                    exit (EXIT_SUCCESS);
                }
                else if(schooce=='y'){
                    longjmp(buf, 1);
                }
                system("CLS");
                sleep(0.1);
                }
            }
      }
                
      else if(kchoice==5){

          exit (EXIT_SUCCESS);
      }
      else if(kchoice==3){
          break;
      }
      else if(kchoice==4){
          longjmp(buf, 1);
      }
            }
        }
             }
        
}
}; 

void Header(Organization a){
    system("CLS");
    sleep(0.1);
    cout << "\n"<<endl;
    cout << "            ";
    for (int i=0;i<=l;i++){
    cout << "-";
    if (i==l)
    cout << "-"<<endl;}
    cout << "            |"<<orgn<<"|"<<endl;
    cout << "            ";
    for (int i=0;i<=l;i++){
    cout << "-";
     if (i==l)
    cout << "-"<<endl;}
    
    cout << "            ";
    cout << "No profit Organization\n\n\n"<<endl;
}


int main (){
    int pchoice,nchoice,k=1,l;
    string choice,n;
    Admin a;
    cout << "Organization name: ";
    getline(cin,orgn);
    Organization org(orgn) ;
    Material m1("rice","white,long,chinese",1,1,3,5);
    Material m2("milk","dairy bad for the planet",2,2,6,4);
    Material m3("sugar","vegan",3,7,6,3);
    Service s1("MedicalSupport","Doctor help",4);
    Service s2("NurserySupport","Nurse help",5);
    Service s3("BabySitting","Sitter help",6);
    Beneficiary B1 ("Alex" , 1111 ,3);
    Beneficiary B2 ("kostas" , 222 ,62);
    Donator D1("Katerina",3333);
    Entity e1=m1;
    Entity e2=m2;
    Entity e6=s3;
    org.addMaterial(m1);
    org.addMaterial(m2);
    org.addMaterial(m3);
    org.addService(s1);
    org.addService(s2);
    org.addService(s3);
    org.addEntity(e1);
    org.addEntity(e2);
    org.addEntity(e6);
    org.listEntities();
    org.insertBeneficiary(B1);
    org.insertBeneficiary(B2);
    org.listBeneficiaries();
    org.insertDonator(D1);
   org.listDonators();
    system("CLS");
    sleep(0.1);
    while(true){
    system("CLS");
    sleep(0.1);
    int phonenumber;
    setjmp(buf);
    system("CLS");
    sleep(0.1);
    l=orgn.length();
    cout << "\n"<<endl;
    cout << "            ";
    for (int i=0;i<=l;i++){
    cout << "-";
    if (i==l)
    cout << "-"<<endl;}
    cout << "            |"<<org.name<<"|"<<endl;
    cout << "            ";
    for (int i=0;i<=l;i++){
    cout << "-";
     if (i==l)
    cout << "-"<<endl;}
    
    cout << "            ";
    cout << "No profit Organization\n\n\n"<<endl;
    cout << "1] Phone number"<<endl;
    cout << "2] Create Account"<<endl;
    cout <<": ";
    cin >> nchoice;
     if (nchoice==1){
    Header(org);
    cout << "Phone number:";
    cin >> phonenumber;
     for(list<Donator>::iterator it = org.donatorList.begin(); it!= org.donatorList.end(); ++it)
  { 
                    Donator item = *it;
                    if (item.phone==phonenumber){
                        Menu m;
                         m.menuDonator(item,org);
                         k=0;
                    }
                   
                    

                    
  }
   for(list<Beneficiary>::iterator it = org.beneficiaryList.begin(); it!= org.beneficiaryList.end(); ++it)
  { 
                    Beneficiary item = *it;
                    if (item.phone==phonenumber){
                        Menu m;
                         m.menuBeneficiary(item,org);
                       k=0;
                    }
                     
  }
    a=org.getAdmin();
    if (phonenumber==a.phone) 
    {   Menu m;
        m.menuAdmin(a,org);
        k=0;
    }
    if (k==1) 
    {   
        cout << "\n You are not appear in the system \n   Do you want to be yes or no?"<<endl;
        cout << "\n->";
        cin >> choice;
        
            if (choice=="yes"){
                 Header(org);
                 cout << "\n Which status:"<<endl;
                 cout << " 1]Admin \n 2]Donator \n 3]Beneficiary"<<endl;
                 cout << "\n->";
                 cin >>pchoice;
                 if (pchoice==1){
                    Header(org);
                    org.setAdmin();
                    a=org.getAdmin();
                    Menu m;
                    m.menuAdmin(a,org);
                }
                else if(pchoice==2){
                        Header(org);
                        int p;
                        string an,reminder;
                        
                        getline(cin,reminder);
                         cout << "Donator name: ";
                         getline(cin,an);
                        cout << "Donator phone: ";
                        cin >> p ;
                        getline(cin,reminder);
                        Donator l(an,p);
                        org.insertDonator(l);
                        Menu m;
                        m.menuDonator(l,org);
                        org.listDonators();
                        
                        
                }
                else if(pchoice==3){
                        Header(org);
                        int p,f;
                        string an,reminder;
                        
                        getline(cin,reminder);
                         cout << "Beneficiary name: ";
                         getline(cin,an);
                        cout << "Beneficiary phone: ";
                        cin >> p ;
                        cout << "family members number: ";
                        cin >> f ;
                        getline(cin,reminder);
                        Beneficiary b(an,p,f);
                        org.insertBeneficiary(b);
                        Menu m;
                        m.menuBeneficiary(b,org);
                        org.listBeneficiaries();

                }
                
            }
            else if (choice=="no"){
                     cout << "\n Goodbye Thank you for consider to be kind for a moment.";
            }
       
    
    }
     }
    else if (nchoice==2){
        Header(org);
        cout << "\n Which status:"<<endl;
                 cout << " 1]Donator \n 2]Beneficiary"<<endl;
                 cout << "\n->";
                 cin >>pchoice;
                 if (pchoice==1){
                      Header(org);
                        int p;
                        string an,reminder;
                        
                        getline(cin,reminder);
                         cout << "Donator name: ";
                         getline(cin,an);
                        cout << "Donator phone: ";
                        cin >> p ;
                        getline(cin,reminder);
                        Donator l(an,p);
                        org.insertDonator(l);
                        Menu m;
                        m.menuDonator(l,org);
                        org.listDonators();
                }
                else if(pchoice==2){
                        Header(org);
                        int p,f;
                        string an,reminder;
                        
                        getline(cin,reminder);
                         cout << "Beneficiary name: ";
                         getline(cin,an);
                        cout << "Beneficiary phone: ";
                        cin >> p ;
                        cout << "family members number: ";
                        cin >> f ;
                        getline(cin,reminder);
                        Beneficiary b(an,p,f);
                        org.insertBeneficiary(b);
                        Menu m;
                        m.menuBeneficiary(b,org);
                        org.listBeneficiaries();



                }
            }
    }
    return 0;
}