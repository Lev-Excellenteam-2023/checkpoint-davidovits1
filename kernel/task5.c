#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/skbuff.h>

static struct nf_hook_ops nfho;

// Netfilter hook function
static unsigned int hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    struct iphdr *ip_header;
    ip_header = ip_hdr(skb);
	if(ip_header)
	{
	   printk(KERN_INFO "Received packet: Source IP %pI4, Dest IP %pI4\n",
           &ip_header->saddr, &ip_header->daddr);
	}


    return NF_ACCEPT;
}

// Module initialization
static int __init LKM_init(void)
{
    nfho.hook = hook_func;
    nfho.hooknum = NF_INET_PRE_ROUTING;
    nfho.pf = PF_INET;
    nfho.priority = NF_IP_PRI_FIRST;

    nf_register_net_hook(&init_net, &nfho);

    printk(KERN_INFO "Netfilter hook module loaded\n");
    return 0;
}

// Module cleanup
static void __exit LKM_exit(void)
{
    nf_unregister_net_hook(&init_net, &nfho);
    printk(KERN_INFO "Netfilter hook module unloaded\n");
}


module_init(LKM_init);
module_exit(LKM_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("david ovits david cohen");
MODULE_DESCRIPTION("Prints the destination and source ip");
MODULE_VERSION("0.01");
