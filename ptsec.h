#include <linux/security.h>
#include <linux/fs.h>

enum tdm_trust_status {
	UNTRUSTED = 0x00,
	TRUSTED,
	UNKNOWN,
};

typedef short int8;

struct degree{
	int t1;
	int t2;
	int cpu_usage;
	int mem_usage;
	int8 deg;
	int8 thd;
	enum tdm_trust_status sts;
} __attribute__((packed));

typedef struct degree tdm_value;

struct cert_pt {
	int cert_no;
	char *cert_name;
};

struct inode_pt {
	int pt_no;
	struct cert_pt *pt_cert;
	int pt_flag;
};

struct task_pt {
	struct cert_pt *pt_cert;
	int pt_flag;
};

struct inode_pt *new_inode_pt(struct cert_pt *pt_cert, int i_ino);
struct task_pt *new_task_pt(struct cert_pt *pt_cert, gfp_t gfp);

static inline struct cert_pt *pt_of_inode(const struct inode *ipp)
{
	struct inode_pt *sip = ipp->i_security;
	return sip->pt_cert;
}

static inline struct cert_pt *pt_of_task(const struct task_pt *tpp)
{
	return tpp->pt_cert;
}

static inline struct cert_pt *pt_of_current(void)
{
	return pt_of_task(current_security());
}
/*  
static inline char *smk_of_forked(const struct task_pt *tpp)
{
	return tpp->pt_forked;
}
*/

