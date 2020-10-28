#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;



class Node
{

    int value ;
    string name;

public :

   Node()
   {
       name="";
       value=0;
   }
   Node (string n)
   {
       name=n;
       value=0;

   }
   Node (string n , int v)
   {
       name =n;
       value =v;

   }
    void Set_name ( string n)

    {
        name=n;
    }

    string Get_name (void)
    {
        return name;
    }

    void Set_value (  int v)

    {
        value =v;
    }

    int Get_value (void)
    {

        return value;
    }
   void printnode()
   {
       cout << name<<"="<<value<<endl;
   }
};


class Gate
{

protected:

    Node * input1;
    Node * input2;
    Node * output;

public :

    Gate ()
    {
        input1=NULL;
        input2=NULL;
        output=NULL;

    }
    void Set_input1 (Node * n)
    {
      input1 = n;
    }

    void Set_input2 ( Node * n)
    {
        input2 = n;
    }


    void Set_output ( Node * n)
    {
        output = n;
    }

    Node * Get_input1 ( void)

    {
        return input1;
    }

     Node * Get_input2 (void)

    {
        return input2;
    }

    Node * Get_output (void)
    {

        return  output;
    }

    virtual void Calc_output (void) =0;

};



class ANDGate : public Gate

{

public :

    void Calc_output ()

    {

        if ((input1 ->Get_value())&& ( input2 ->Get_value()) )

        {
            output ->Set_value(1);
        }else
        {
            output ->Set_value(0);
        }
    }


};



class ORGate :  public Gate

{
     public :


         void Calc_output ()
         {

             if ((input1 ->Get_value()) || ( input2 ->Get_value() ))

            {
                   output ->Set_value(1);
            }

             else
            {
              output ->Set_value(0);
            }

        }
};





class NANDGate : public Gate
{

   public :
       void Calc_output ()

       {

          if ((input1 ->Get_value()== 1)&& ( input2 ->Get_value() ==  1))

         {
            output ->Set_value(0);
         } else
          {
              output ->Set_value(1);
          }
       }

};

class NORGate : public Gate
{
  public :

       void Calc_output ()

       {

                    if ((input1 ->Get_value()== 0)&& ( input2 ->Get_value() ==  0))

            {
                   output ->Set_value(1);
            }

             else
            {
              output ->Set_value(0);
            }

       }


};



class XORGate : public Gate
{


    public :

     void Calc_output ()

       {

           if ((input1 ->Get_value()== 0)&& ( input2 ->Get_value() ==  0))

            {
                   output ->Set_value(0);
            }

             else if  ((input1 ->Get_value()== 1)&& ( input2 ->Get_value() ==  1))
            {
              output ->Set_value(0);
            }
            else
            {

                output ->Set_value(1);

            }


       }


};


class XNORGate : public Gate
{

public :

     void Calc_output ()

       {

           if ((input1 ->Get_value()== 0)&& ( input2 ->Get_value() ==  0))

            {
                   output ->Set_value(1);
            }

             else if  ((input1 ->Get_value()== 1)&& ( input2 ->Get_value() ==  1))
            {
              output ->Set_value(1);
            }
            else
            {

                output ->Set_value(0);

            }


       }



};

class NOTGate :public Gate
{

    public :

     void Calc_output ()

       {

           if ((input1 ->Get_value()== 0))

            {
                   output ->Set_value(1);
            }

            else
            {

                   output ->Set_value(0);

            }


       }




};

class simulator
{

        vector <Gate *> GA  ;
        vector <Node *> NA ;

    public:

        simulator()
        {

        }


        int Get_nodesize ()
        {


            return NA.size();
        }

        int Get_gatesize ()
        {
            return GA.size();

        }
        Node* Findnode(string name)
        {


            for (int i =0 ; i< NA.size(); i++)
            {

                if ( NA[i]->Get_name()== name)

                {
                    return NA[i];
                }

            }

            return NULL;


        }

  Node * Addnode (string name)
  {

      Node * p =new Node(name);
      NA.push_back(p);
      return p;


  }


  Node * findorAdd ( string name)
  {

      Node * p = Findnode( name);
      if  ( p != NULL)

      {
          return p;

      }

       return Addnode ( name);



  }

  Gate * Addgate (string type)
  {

      Gate * p =NULL;
      if (type == "AND")
      {
          p = new ANDGate();

      }
      else if (type == "OR")
    {
          p = new ORGate();

      }
        else if (type == "XOR")
    {
          p= new XORGate();

    }
    else if (type == "XNOR")
    {
          p= new XNORGate();

    }
    else if (type == "NAND")
    {
          p = new NANDGate();

    }
     else if (type == "NOR")
    {
          p= new NORGate();

    }
      GA.push_back(p);
      return p;




  }

  void print_all()
  {

      for(int i=0;i< NA.size();i++)
      {

          cout << NA[i]->Get_name()<<"="<< NA[i]->Get_value()<<endl;
      }

  }

 void sim()
 {
    for (int j=0 ;j <GA.size();j++)
    {

      for ( int i=0;i<GA.size();i++)

       {
           GA[i]-> Calc_output();
       }
    }

 }


  void load (const char * name_file)
{
   fstream inputfile;
    inputfile.open(name_file);
    if (!inputfile) {
    cerr << "Unable to open file datafile.txt";
    exit(1);   // call system to stop
}
    while(!inputfile.eof())
    {
        string s;
        inputfile>> s;
        if(s == "SET")
        {
            string node_input;
            short  node_value;
            inputfile>> node_input>> node_value;
            findorAdd(node_input) ->Set_value(node_value);

        }else if (s =="SIM")
        {

            sim();
        }else if (s == "OUT")
        {

            string n;

             inputfile>>n;
             if( n == "ALL")
             {
                print_all();

             }else
             {
          Node *ptr1=  findorAdd(n);
          ptr1->printnode();
             }
        }else

        {
            Gate *P =Addgate(s);
            string N1,N2,N3;
            inputfile >>N1;
            inputfile >>N2;
            inputfile >>N3;
            P->Set_input1((   findorAdd(N1) ));
            P->Set_input2((   findorAdd(N2) ));
            P->Set_output((    findorAdd(N3) ));

        }

    }


    inputfile.close();

}

  ~simulator()

  {

      for(int i=0; i<NA.size();i++)
      {
          delete(NA[i]);
      }

          for(int i=0; i<GA.size();i++)
      {
          delete(GA[i]);
      }
  }
};


int main()
{

 simulator  s;
 s.load("C:\\code_block\\simualtor_proj\\simu.txt");
 return 0;

}
