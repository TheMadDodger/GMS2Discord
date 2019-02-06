#pragma once
enum DiscordData : int unsigned
{
	Details,
	State,
	LargeImageKey,
	SmallImageKey,
	LargeImageText,
	SmallImageText,
	MAX_DISCORD_DATA,
};

class DiscordIntegration
{
public:
	DiscordIntegration(const std::string &applicationId, const std::string &steamID = "");
	virtual ~DiscordIntegration();

	// Base
	void Initialize();
	void PreCleanUp();
	void Update();

	// Setting data
	void SetData(double key, std::string details);

private:
	// Callbacks
	static void HandleDiscordReady(const DiscordUser* request);
	static void HandleDiscordDisconnected(int errorCode, const char* message);
	static void HandleDiscordError(int errorCode, const char* message);
	static void HandleDiscordJoinGame(const char* joinSecret);
	static void HandleDiscordSpectateGame(const char* spectateSecret);
	static void HandleDiscordJoinRequest(const DiscordUser* request);

private:
	// Members
	std::string m_ApplicationId;
	std::string m_SteamID;
	DiscordRichPresence m_RichPresense;

	std::vector<std::string> m_Data;
};

//char buffer[256];
//discordPresence.state = "In a Group";
//sprintf(buffer, "Ranked | Mode: %d", GameEngine.GetMode());
//discordPresence.details = buffer;
//discordPresence.endTimestamp = time(0) + 5 * 60;
//discordPresence.largeImageKey = "canary-large";
//discordPresence.smallImageKey = "ptb-small";
//discordPresence.partyId = GameEngine.GetPartyId();
//discordPresence.partySize = 1;
//discordPresence.partyMax = 6;
//discordPresence.matchSecret = "4b2fdce12f639de8bfa7e3591b71a0d679d7c93f";
//discordPresence.spectateSecret = "e7eb30d2ee025ed05c71ea495f770b76454ee4e0";
//discordPresence.instance = 1;
//Discord_UpdatePresence(&discordPresence);