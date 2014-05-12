#
# Makefile for building the BASC module as part of the kernel tree.
#

obj-$(CONFIG_SECURITY_PTSEC) := ptsec.o

ptsec-y := ptlsm.o 
