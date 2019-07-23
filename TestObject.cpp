#include "DXUT.h"
#include "TestObject.h"

void TestObject::Init()
{
	TouchEvent = CreateEvent(TouchEventArgs, OnMouseClick);
	INPUT.OnLeftMouseClick += TouchEvent;

	AC(Transform);

	ACR(MeshRenderer)
		.SetMesh(FIND(Mesh, "Test"))
		.SetShader(FIND(Shader,"SkyBoxShader"));

	SetRenderBegin(LAMBDA{ DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, false); });
	SetRenderEnd(LAMBDA{ DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, true); });
}

void TestObject::Update()
{
	if (INPUT.GetKeyPress(VK_UP))
		transform->rotation.x += Time::DeltaTime() * 5;
	if (INPUT.GetKeyPress(VK_DOWN))
		transform->rotation.x -= Time::DeltaTime() * 5;

	if (INPUT.GetKeyPress(VK_LEFT))
		transform->rotation.y += Time::DeltaTime() * 5;
	if (INPUT.GetKeyPress(VK_RIGHT))
		transform->rotation.y -= Time::DeltaTime() * 5;
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
