#pragma once
class CServerNetwork
{
public:
	CServerNetwork();
	~CServerNetwork();

	/* Server Configuration */
	static int ServerPort;
	static int ServerSecret;

	//------------------------------------------------------------------------------------------------

	static HANDLE server_handle;
	static bool server_running, console_active;
	static librg_ctx_t ctx;
	static std::vector<librg_entity_t*> playerEntities;
	static std::vector<librg_entity_t*> otherEntities;

	//------------------------------------------------------------------------------------------------

	static void PedCreateEvent(librg_message_t* msg);
	static void VehCreateEvent(librg_message_t* msg);

	//------------------------------------------------------------------------------------------------

	static void on_connect_request(librg_event_t *event);
	static void on_connect_accepted(librg_event_t *event);
	static void on_creating_entity(librg_event_t *event);
	static void on_entity_update(librg_event_t *event);
	static void on_disconnect(librg_event_t* event);
	static void on_stream_update(librg_event_t *event);

	//------------------------------------------------------------------------------------------------

	static void measure(void *userptr);
	static void server_thread();
};

