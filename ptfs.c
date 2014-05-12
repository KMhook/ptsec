/*
 * =====================================================================================
 *
 *       Filename:  ptfs.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年03月04日 02时11分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <linux/kernel.h>
#include <linux/vmalloc.h>
#include <linux/security.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/seq_file.h>
#include <linux/ctype.h>
#include <linux/audit.h>
#include <linux/magic.h>


static const struct file_operations pt_test_ops = {
	.open = pt_open_test,
	.read = pt_read_test,
	.write = pt_write_test,
}


static int pt_fill_super(struct super_block *sb,
		void *data, int silent)
{
	int rc;
	struct inode *root_inode;

	static struct tree_descr pt_files[] = {
		[PT_TEST] = {
			"test", &pt_test_ops, S_IRUGO|S_IWUSR},
		{""}
	};

	rc = simple_fill_super(sb, PT_MAGIC, pt_files);

	if (rc != 0) {
		printk(KERN_ERR "%s failed %d while creating inodes\n",
				__func__, rc);
		return rc;
	}

	root_inode = sb->s_root->d_inode;

	return 0;
}

static struct dentry *pt_mount(struct file_system_type *fs_type,
		int flags, const char *dev_name, void *data)
{
	return mount_single(fs_type, flags, data, pt_fill_super);
}

static struct file_system_type pt_fs_type = {
	.name = "ptfs",
	.mount = pt_mount,
	.kill_sb = kill_litter_super,
};

