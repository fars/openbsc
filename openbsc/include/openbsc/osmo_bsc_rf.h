#ifndef OSMO_BSC_RF
#define OSMO_BSC_RF

#include <openbsc/gsm_data.h>
#include <osmocom/core/write_queue.h>
#include <osmocom/core/timer.h>

enum osmo_bsc_rf_opstate {
	OSMO_BSC_RF_OPSTATE_INOPERATIONAL,
	OSMO_BSC_RF_OPSTATE_OPERATIONAL,
};

enum osmo_bsc_rf_adminstate {
	OSMO_BSC_RF_ADMINSTATE_UNLOCKED,
	OSMO_BSC_RF_ADMINSTATE_LOCKED,
};

enum osmo_bsc_rf_policy {
	OSMO_BSC_RF_POLICY_OFF,
	OSMO_BSC_RF_POLICY_ON,
	OSMO_BSC_RF_POLICY_GRACE,
	OSMO_BSC_RF_POLICY_UNKNOWN,
};


struct gsm_network;

struct osmo_bsc_rf {
	/* the value of signal.h */
	int policy;
	struct osmo_fd listen;
	struct gsm_network *gsm_network;

	const char *last_state_command;

	/* delay the command */
	char last_request;
	struct osmo_timer_list delay_cmd;

	/* verify that RF is up as it should be */
	struct osmo_timer_list rf_check;

	/* some handling for the automatic grace switch */
	struct osmo_timer_list grace_timeout;
};

struct osmo_bsc_rf_conn {
	struct osmo_wqueue queue;
	struct osmo_bsc_rf *rf;
};

enum osmo_bsc_rf_opstate osmo_bsc_rf_get_opstate_by_bts(struct gsm_bts *bts);
enum osmo_bsc_rf_adminstate osmo_bsc_rf_get_adminstate_by_bts(struct gsm_bts *bts);
enum osmo_bsc_rf_policy osmo_bsc_rf_get_policy_by_bts(struct gsm_bts *bts);
struct osmo_bsc_rf *osmo_bsc_rf_create(const char *path, struct gsm_network *net);

#endif