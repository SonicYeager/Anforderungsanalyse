#include "gmock/gmock.h"
#include "../SLFGameBackend/Client.h"
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

TEST(TestClient, ReceiveData_ReceiveData_CallReceiveData)
{
	::testing::StrictMock<FakeNetworkSource> fns{};
	Client c{&fns};
	EXPECT_CALL(fns, ReceiveData());

	c.ReceiveData();
}

TEST(TestClient, WriteToHost_WriteToHost_CallWriteToHost)
{
	::testing::StrictMock<FakeNetworkSource> fns{};
	Client c{ &fns };
	EXPECT_CALL(fns, WriteToHost(ByteStream{ '0','0','\0' }));

	c.WriteToHost({'0','0','\0'});
}

TEST(TestClient, ConnectToServer_ConnectToServer_CallConnectToServer)
{
	::testing::StrictMock<FakeNetworkSource> fns{};
	Client c{ &fns };
	EXPECT_CALL(fns, ConnectToServer("ip"));

	c.ConnectToServer("ip");
}