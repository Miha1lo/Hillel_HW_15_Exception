
#include <iostream>
#include <exception>


class BaseException : public std::exception
{
public:
   const char* what() const noexcept override
   {
      return "Base exception";
   }
};

class Derived1Exception : public BaseException
{
public:
   const char* what() const noexcept override
   {
      return "Derived1 exception";
   }
};

class Derived2Exception : public BaseException
{
public:
   const char* what() const noexcept override
   {
      return "Derived2 exception";
   }
};

class Base
{
public:
   virtual void performAction()
   {
      throw BaseException();
   }
};

class Derived1 : public Base
{
public:
   void performAction() override
   {
      throw Derived1Exception();
   }
};

class Derived2 : public Base
{
public:
   void performAction() override
   {
      throw Derived2Exception();
   }
};


void handleAction(Base& obj)
{
   try
   {
      obj.performAction();
   }
   catch (const Derived1Exception& e)
   {
      std::cerr << "Exception: " << e.what() << std::endl;
   }
   catch (const Derived2Exception& e)
   {
      std::cerr << "Exception: " << e.what() << std::endl;
   }
   catch (const BaseException& e)
   {
      std::cerr << "Exception: " << e.what() << std::endl;
   }
   catch (...)
   {
      std::cerr << "Another exception" << std::endl;
   }
}

int main()
{
   Derived1 d1;
   Derived2 d2;
   Base b;

   handleAction(d1);  // Derived1Exception
   handleAction(d2);  // Derived2Exception
   handleAction(b);   // BaseException

   return 0;
}

