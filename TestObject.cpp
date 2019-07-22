#include "DXUT.h"
#include "TestObject.h"

void TestObject::Init()
{
	TouchEvent = CreateEvent(TouchEventArgs, OnMouseClick);
	INPUT.OnLeftMouseClick += TouchEvent;
}

void TestObject::Update()
{
} 

void TestObject::Render()
{

}

void TestObject::Destroy()
{
	INPUT.OnLeftMouseClick.SafeRemove(TouchEvent);
}

void TestObject::OnMouseClick(object sender, TouchEventArgs args)
{
	cout << args.MousePosition << endl;
}
