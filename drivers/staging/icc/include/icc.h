/*
 * Copyright 2010-2018 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */

#ifndef _ICC_H
#define _ICC_H

/* sm protocol */
/* compose type enumeration value from protocol & subtype */
#define SM_MSG_TYPE(protocol, subtype) (((protocol)<<24)|(subtype))

/* extract subtype from type enumeration value */
#define SM_MSG_SUBTYPE(type) ((type)&0xffffff)

/* extract protocol from type enumeration value */
#define SM_MSG_PROTOCOL(type) (((type)>>24)&0xff)

#ifdef CONFIG_ICC_DEBUG
#define sm_debug(fmt, ...) \
	printk(KERN_CRIT "sm_debug:"pr_fmt(fmt), ##__VA_ARGS__)
#else
#define sm_debug(fmt, ...) \
	({ if (0) printk(KERN_CRIT "sm_debug:"pr_fmt(fmt), ##__VA_ARGS__); 0; })
#endif

enum {
	SP_GENERAL = 0,
	SP_CORE_CONTROL,
	SP_TASK_MANAGER,
	SP_RES_MANAGER,
	SP_PACKET,
	SP_SESSION_PACKET,
	SP_SCALAR,
	SP_SESSION_SCALAR,
	SP_MAX,
};

enum icc_queue_attr {
	ICC_QUEUE_ATTR_STATUS = 0,
	ICC_QUEUE_ATTR_MAX,
};

enum icc_queue_status {
	ICC_QUEUE_STOP = 0,
	ICC_QUEUE_INIT,
	ICC_QUEUE_READY,
	ICC_QUEUE_STATUS_MAX,
};

enum {
	RESMGR_TYPE_PERIPHERAL = 0,
	RESMGR_TYPE_GPIO,
	RESMGR_TYPE_SYS_IRQ,
	RESMGR_TYPE_DMA,
	RESMGR_TYPE_MAX,
};

enum {
	WAIT_OTHER = 0,
	WAIT_OPEN_PKTCHAN,
	WAIT_OPEN_SCLCHAN,
	WAIT_SEND,
	WAIT_RECV,
	WAIT_GET_ENDPT,
	WAIT_MAX,
};

#define EP_RESMGR_SERVICE 0

#define RES_TYPE_OFFSET  12
#define RES_TYPE_MASK    0xF
#define RES_SUBID_MASK   0xFFF

#define RESMGR_ID(type, subid) ((type << RES_TYPE_OFFSET) | (subid & RES_SUBID_MASK))
#define RESMGR_SUBID(id)       (id & RES_SUBID_MASK)
#define RESMGR_TYPE(id)        ((id >> RES_TYPE_OFFSET) & RES_TYPE_MASK)

#define SM_UNCONNECT 0
#define SM_CONNECT 0x1
#define SM_CONNECTING 0x2
#define SM_OPEN 0x4
#define SM_ACTIVE 0x8

#define SM_BAD_ENDPOINT SM_MSG_TYPE(SP_GENERAL, 0)
#define SM_BAD_MSG SM_MSG_TYPE(SP_GENERAL, 1)
#define SM_QUERY_MSG SM_MSG_TYPE(SP_GENERAL, 2)
#define SM_QUERY_ACK_MSG SM_MSG_TYPE(SP_GENERAL, 3)

#define SM_CORE_START		SM_MSG_TYPE(SP_CORE_CONTROL, 0)
#define SM_CORE_STARTED		SM_MSG_TYPE(SP_CORE_CONTROL, 1)
#define SM_CORE_STOP		SM_MSG_TYPE(SP_CORE_CONTROL, 2)
#define SM_CORE_STOPPED		SM_MSG_TYPE(SP_CORE_CONTROL, 3)
#define SM_CORE_RESET		SM_MSG_TYPE(SP_CORE_CONTROL, 4)
#define SM_CORE_RESETED		SM_MSG_TYPE(SP_CORE_CONTROL, 5)

#define SM_TASK_RUN		SM_MSG_TYPE(SP_TASK_MANAGER, 0)
#define SM_TASK_RUN_ACK		SM_MSG_TYPE(SP_TASK_MANAGER, 1)
#define SM_TASK_KILL		SM_MSG_TYPE(SP_TASK_MANAGER, 2)
#define SM_TASK_KILL_ACK	SM_MSG_TYPE(SP_TASK_MANAGER, 3)

#define SM_RES_MGR_REQUEST	SM_MSG_TYPE(SP_RES_MANAGER, 0)
#define SM_RES_MGR_REQUEST_OK	SM_MSG_TYPE(SP_RES_MANAGER, 1)
#define SM_RES_MGR_REQUEST_FAIL	SM_MSG_TYPE(SP_RES_MANAGER, 2)
#define SM_RES_MGR_FREE		SM_MSG_TYPE(SP_RES_MANAGER, 3)
#define SM_RES_MGR_FREE_DONE	SM_MSG_TYPE(SP_RES_MANAGER, 4)
#define SM_RES_MGR_EXPIRE	SM_MSG_TYPE(SP_RES_MANAGER, 5)
#define SM_RES_MGR_EXPIRE_DONE	SM_MSG_TYPE(SP_RES_MANAGER, 6)
#define SM_RES_MGR_LIST		SM_MSG_TYPE(SP_RES_MANAGER, 7)
#define SM_RES_MGR_LIST_OK	SM_MSG_TYPE(SP_RES_MANAGER, 8)
#define SM_RES_MGR_LIST_DONE	SM_MSG_TYPE(SP_RES_MANAGER, 9)

#define SM_PACKET_READY		SM_MSG_TYPE(SP_PACKET, 0)
#define SM_PACKET_CONSUMED	SM_MSG_TYPE(SP_PACKET, 1)
#define SM_PACKET_ERROR		SM_MSG_TYPE(SP_PACKET, 2)
#define SM_PACKET_ERROR_ACK	SM_MSG_TYPE(SP_PACKET, 3)

#define SM_SESSION_PACKET_CONNECT	SM_MSG_TYPE(SP_SESSION_PACKET, 0)
#define SM_SESSION_PACKET_CONNECT_ACK	SM_MSG_TYPE(SP_SESSION_PACKET, 1)
#define SM_SESSION_PACKET_CONNECT_DONE	SM_MSG_TYPE(SP_SESSION_PACKET, 2)
#define SM_SESSION_PACKET_ACTIVE	SM_MSG_TYPE(SP_SESSION_PACKET, 3)
#define SM_SESSION_PACKET_ACTIVE_ACK	SM_MSG_TYPE(SP_SESSION_PACKET, 4)
#define SM_SESSION_PACKET_CLOSE		SM_MSG_TYPE(SP_SESSION_PACKET, 5)
#define SM_SESSION_PACKET_CLOSE_ACK	SM_MSG_TYPE(SP_SESSION_PACKET, 6)
#define SM_SESSION_PACKET_READY		SM_MSG_TYPE(SP_SESSION_PACKET, 7)
#define SM_SESSION_PACKET_CONSUMED	SM_MSG_TYPE(SP_SESSION_PACKET, 8)
#define SM_SESSION_PACKET_ERROR		SM_MSG_TYPE(SP_SESSION_PACKET, 9)
#define SM_SESSION_PACKET_ERROR_ACK	SM_MSG_TYPE(SP_SESSION_PACKET, 10)

#define SM_SCALAR_8BIT			0
#define SM_SCALAR_16BIT			1
#define SM_SCALAR_32BIT			2
#define SM_SCALAR_64BIT			3

#define SM_SCALAR_READY_8		SM_MSG_TYPE(SP_SCALAR, SM_SCALAR_8BIT)
#define SM_SCALAR_READY_16		SM_MSG_TYPE(SP_SCALAR, SM_SCALAR_16BIT)
#define SM_SCALAR_READY_32		SM_MSG_TYPE(SP_SCALAR, SM_SCALAR_32BIT)
#define SM_SCALAR_READY_64		SM_MSG_TYPE(SP_SCALAR, SM_SCALAR_64BIT)
#define SM_SCALAR_CONSUMED		SM_MSG_TYPE(SP_SCALAR, 4)
#define SM_SCALAR_ERROR			SM_MSG_TYPE(SP_SCALAR, 5)
#define SM_SCALAR_ERROR_ACK		SM_MSG_TYPE(SP_SCALAR, 6)

#define SM_SESSION_SCALAR_READY_8	SM_MSG_TYPE(SP_SESSION_SCALAR, SM_SCALAR_8BIT)
#define SM_SESSION_SCALAR_READY_16	SM_MSG_TYPE(SP_SESSION_SCALAR, SM_SCALAR_16BIT)
#define SM_SESSION_SCALAR_READY_32	SM_MSG_TYPE(SP_SESSION_SCALAR, SM_SCALAR_32BIT)
#define SM_SESSION_SCALAR_READY_64	SM_MSG_TYPE(SP_SESSION_SCALAR, SM_SCALAR_64BIT)
#define SM_SESSION_SCALAR_CONSUMED	SM_MSG_TYPE(SP_SESSION_SCALAR, 4)
#define SM_SESSION_SCALAR_ERROR		SM_MSG_TYPE(SP_SESSION_SCALAR, 5)
#define SM_SESSION_SCALAR_ERROR_ACK	SM_MSG_TYPE(SP_SESSION_SCALAR, 6)
#define SM_SESSION_SCALAR_CONNECT	SM_MSG_TYPE(SP_SESSION_SCALAR, 7)
#define SM_SESSION_SCALAR_CONNECT_ACK	SM_MSG_TYPE(SP_SESSION_SCALAR, 8)
#define SM_SESSION_SCALAR_CONNECT_DONE	SM_MSG_TYPE(SP_SESSION_SCALAR, 9)
#define SM_SESSION_SCALAR_ACTIVE	SM_MSG_TYPE(SP_SESSION_SCALAR, 10)
#define SM_SESSION_SCALAR_ACTIVE_ACK	SM_MSG_TYPE(SP_SESSION_SCALAR, 11)
#define SM_SESSION_SCALAR_CLOSE		SM_MSG_TYPE(SP_SESSION_SCALAR, 12)
#define SM_SESSION_SCALAR_CLOSE_ACK	SM_MSG_TYPE(SP_SESSION_SCALAR, 13)

#ifdef __KERNEL__
#include <linux/types.h>
#include <linux/wait.h>
#include <linux/mutex.h>

void icc_send_ipi_cpu(unsigned int cpu, int irq);
void icc_clear_ipi(unsigned int cpu, int irq);

struct sm_msg {
	uint16_t dst_ep;
	uint16_t src_ep;
	uint32_t type;
	uint32_t length ;
	uint32_t payload;
};

struct sm_message {
	struct list_head next;
	uint16_t dst;
	uint16_t src;
	void *vbuf;
	struct sm_msg msg;
	struct sm_icc_desc *icc_info;
	uint32_t flags;
	bool b_tx_finish;
};

#define SM_MSGQ_LEN 16

/* Simple FIFO buffer */
struct sm_message_queue {
	uint16_t sent;
	uint16_t received; /* head of the queue */
	struct sm_msg messages[SM_MSGQ_LEN];
};

#define SM_MSGQ_NUM		4 /* 2 low bi-direction fifos and 2 high ones */
#define MSGQ_SIZE		(sizeof(struct sm_message_queue) * SM_MSGQ_NUM)

#define DEBUG_MSG_LINE		256
#define DEBUG_MSG_BUF_SIZE	(DEBUG_MSG_LINE * SM_MSGQ_LEN)

struct sm_icc_desc {
	uint32_t peer_cpu;
	struct sm_message_queue *icc_queue;
	struct sm_message_queue *icc_high_queue;
	uint32_t *icc_queue_attribute;
	struct task_struct *iccq_thread;
	wait_queue_head_t iccq_tx_wait;
	uint32_t irq;
	uint32_t notify;
};

struct sm_session {
	struct list_head rx_messages; /*rx queue sm message*/
	struct list_head tx_messages;
	uint32_t	n_avail;
	uint32_t	n_uncompleted;
	uint32_t	local_ep;
	uint32_t	remote_ep; /*remote ep*/
	uint32_t	type;
	pid_t		pid;
	uint32_t	flags;
	int (*handle)(struct sm_message *msg, struct sm_session *session);
	struct sm_proto *proto_ops;
	uint32_t	queue_priority;
	wait_queue_head_t rx_wait;
	bool b_rx_finish;
} __attribute__((__aligned__(4)));

#define MAX_ENDPOINTS 32
#define MAX_SESSIONS 32
#define MAX_TASK_NAME 64
struct sm_session_table {
	struct list_head next_table;
	struct list_head query_message;
	wait_queue_head_t query_wait;
	bool   b_query_finish;
	struct mutex lock;
	uint32_t	nfree;
	uint32_t session_mask;
	uint32_t session_pending;
	uint32_t	bits[(MAX_ENDPOINTS - 1) / BITS_PER_LONG + 1];
	uint16_t	refcnt;
	struct sm_session sessions[MAX_ENDPOINTS];
};

struct sm_proto {
	int (*sendmsg)(struct sm_message *msg, struct sm_session *session);
	int (*recvmsg)(struct sm_msg *msg, struct sm_session *session);
	int (*shutdown)(struct sm_session *session);
	int (*error)(struct sm_msg *msg, struct sm_session *session);
};

struct sm_task {
	int (*task_init)(int argc, char *argv[]);
	void (*task_exit)(void);
	int task_argc;
	char task_argv[3][MAX_TASK_NAME];
};
#define __icc_task __attribute__((section(".icc.text")))
#define __icc_task_data __attribute__((section(".icc.data")))

int sm_send_control_msg(struct sm_session *session, uint32_t remote_ep,
			uint32_t dst_cpu, uint32_t payload,
			uint32_t len, uint32_t type);

struct icc_peer_platform_data {
	uint32_t peerid;
	uint32_t notify;
};

struct icc_platform_data {
	int	node;
	uint32_t peer_count;
	struct icc_peer_platform_data *peer_info;
};

struct icc_peri_resource {
	const char *name;
	struct platform_device *pdev;
	uint16_t resource_id;
};

extern struct icc_peri_resource icc_peri_array[];
#endif

#define CCTRL_CORE1                 1
#define CCTRL_CORE2                 2
#define CMD_CORE_START              _IO('b', 0)
#define CMD_CORE_STOP               _IO('b', 1)
#define CMD_SET_SVECT1              _IO('m', 17)
#define CMD_SET_SVECT2              _IO('m', 18)
#define CMD_SM_SEND                 _IO('m', 3)
#define CMD_SM_CREATE               _IO('m', 4)
#define CMD_SM_CONNECT              _IO('m', 5)
#define CMD_SM_RECV                 _IO('m', 6)
#define CMD_SM_SHUTDOWN             _IO('m', 7)
#define CMD_SM_GET_NODE_STATUS      _IO('m', 8)
#define CMD_SM_GET_SESSION_STATUS   _IO('m', 9)
#define CMD_SM_OPEN                 _IO('m', 10)
#define CMD_SM_CLOSE                _IO('m', 11)
#define CMD_SM_ACTIVE               _IO('m', 12)
#define CMD_SM_REQUEST_UNCACHED_BUF _IO('m', 13)
#define CMD_SM_RELEASE_UNCACHED_BUF _IO('m', 14)
#define CMD_SM_QUERY_REMOTE_EP      _IO('m', 15)
#define CMD_SM_WAIT                 _IO('m', 16)

struct sm_node_status {
	uint32_t session_mask;
	uint32_t session_pending;
	uint32_t nfree;
};

struct sm_session_status {
	uint32_t	n_avail;
	uint32_t	n_uncompleted;
	uint32_t	local_ep;
	uint32_t	remote_ep;
	uint32_t	type;
	uint32_t	pid;
	uint32_t	flags;
};

struct sm_packet {
	uint32_t session_idx;
	uint32_t local_ep;
	uint32_t remote_ep;
	uint32_t type;
	uint32_t flag;
	uint32_t dst_cpu;
	uint32_t src_cpu;
	uint32_t buf_len;
	uint32_t paddr;
	uint32_t queue_priority;
	void *buf;
	uint32_t param_len;
	void *param;
	uint32_t payload;
	int timeout;
};

typedef struct {
	char label[32];				/* owner name */
	uint16_t count;				/* resource number in next array */
	uint32_t resources_array;		/* address of the resource ID array */
} resources_t;


#define SM_SCALAR_CMD(x) ((x) >> 16 & 0xffff)
#define SM_SCALAR_CMDARG(x) ((x) & 0xffff)
#define SM_SCALAR_CMD_HEAD 0xFE
#define SM_SCALAR_ACK_HEAD   0xFF
#define SM_SCALAR_CMD_GET_SESSION_ID        0x1
#define SM_SCALAR_CMD_GET_SESSION_TYPE      0x2

#define MK_SM_SCALAR_CMD(x) (((x) & 0xffff) | (SM_SCALAR_CMD_HEAD << 16))
#define MK_SM_SCALAR_CMD_ACK(x) (((x) & 0xffff) | (SM_SCALAR_ACK_HEAD << 16))

#define L3_TYPE_AUDIO 1
#define L3_TYPE_VIDEO 2
#define L3_TYPE_ENCODE 4
#define L3_TYPE_DECODE 8

struct l3_proto_head {
	unsigned int type;
	unsigned int todo;
	unsigned int chunk_addr;
	unsigned int chunk_size;
	unsigned int status;
};

#endif
