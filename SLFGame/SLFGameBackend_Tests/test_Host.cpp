#include "gmock/gmock.h"
#include "../SLFGameBackend/Host.h"
#include "../SLFGameBackend/NetworkSource.h"

class FakeNetworkSource : public NetworkSource
{
public:
	MOCK_METHOD(LobbyCode, StartServer, (), (override));
	MOCK_METHOD(void, ConnectToServer, (const LobbyCode&), (override));
	MOCK_METHOD(void, WriteTo, (const ByteStream&, int), (override));
	MOCK_METHOD(void, WriteToHost, (const ByteStream&), (override));
	MOCK_METHOD(void, Broadcast, (const ByteStream&), (override));
	MOCK_METHOD(ByteStream, ReceiveData, (), (override));
	MOCK_METHOD(ByteStream, ReceiveData, (int), (override));
};

TEST(HostClient, ReceiveData_ReceiveData_CallReceiveDataFromLast)
{
	::testing::StrictMock<FakeNetworkSource> fns{};
	Host c{ &fns };
	EXPECT_CALL(fns, ReceiveData(10));

	c.ReceiveData(10);
}

TEST(HostClient, WriteTo_WriteTo_CallWriteToFirst)
{
	::testing::StrictMock<FakeNetworkSource> fns{};
	Host c{ &fns };
	EXPECT_CALL(fns, WriteTo(ByteStream{ '0','0','\0' }, 0));

	c.WriteTo({ '0','0','\0' }, 0);
}

TEST(HostClient, StartServer_StartServer_CallStartServer)
{
	::testing::StrictMock<FakeNetworkSource> fns{};
	Host c{ &fns };
	EXPECT_CALL(fns, StartServer());

	c.StartServer();
}

TEST(HostClient, Broadcast_Broadcast_CallBroadcast)
{
	::testing::StrictMock<FakeNetworkSource> fns{};
	Host c{ &fns };
	EXPECT_CALL(fns, Broadcast(ByteStream{'0','0','\0'}));

	c.Broadcast({ '0','0','\0' });
}