#ifndef _INHERIT_H_
#define _INHERIT_H_

class Base
{
public:
  virtual ~Base() = default;

  virtual int Foo();

private:
};

class Derived : public Base
{
public:
  virtual int Foo();

private:
};

#endif // _INHERIT_H_
