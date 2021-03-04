#pragma once
#include "../SLFGameBackend/NetworkSource.h"
#include "../SLFGameBackend/Host.h"

struct Interactor
{
	Interactor(Network*);
	void DoSomething();

private:
	Network* m_pNetwork;
};

inline Interactor::Interactor(Network* n) 
	: m_pNetwork(n)
{}

void Interactor::DoSomething()
{
	m_pNetwork->StartServer();
	m_pNetwork->WriteToHost(ByteStream());
}

void main()
{	
	HostLogic h{};
	Interactor i{&h};
	i.DoSomething();
}