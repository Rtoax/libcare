
server:     file format elf64-x86-64


Disassembly of section .init:

0000000000400750 <_init>:
  400750:	f3 0f 1e fa          	endbr64 
  400754:	48 83 ec 08          	sub    $0x8,%rsp
  400758:	48 8b 05 91 08 20 00 	mov    0x200891(%rip),%rax        # 600ff0 <__gmon_start__>
  40075f:	48 85 c0             	test   %rax,%rax
  400762:	74 02                	je     400766 <_init+0x16>
  400764:	ff d0                	callq  *%rax
  400766:	48 83 c4 08          	add    $0x8,%rsp
  40076a:	c3                   	retq   

Disassembly of section .plt:

0000000000400770 <.plt>:
  400770:	ff 35 92 08 20 00    	pushq  0x200892(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400776:	ff 25 94 08 20 00    	jmpq   *0x200894(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40077c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400780 <recv@plt>:
  400780:	ff 25 92 08 20 00    	jmpq   *0x200892(%rip)        # 601018 <recv@GLIBC_2.2.5>
  400786:	68 00 00 00 00       	pushq  $0x0
  40078b:	e9 e0 ff ff ff       	jmpq   400770 <.plt>

0000000000400790 <setsockopt@plt>:
  400790:	ff 25 8a 08 20 00    	jmpq   *0x20088a(%rip)        # 601020 <setsockopt@GLIBC_2.2.5>
  400796:	68 01 00 00 00       	pushq  $0x1
  40079b:	e9 d0 ff ff ff       	jmpq   400770 <.plt>

00000000004007a0 <htons@plt>:
  4007a0:	ff 25 82 08 20 00    	jmpq   *0x200882(%rip)        # 601028 <htons@GLIBC_2.2.5>
  4007a6:	68 02 00 00 00       	pushq  $0x2
  4007ab:	e9 c0 ff ff ff       	jmpq   400770 <.plt>

00000000004007b0 <htonl@plt>:
  4007b0:	ff 25 7a 08 20 00    	jmpq   *0x20087a(%rip)        # 601030 <htonl@GLIBC_2.2.5>
  4007b6:	68 03 00 00 00       	pushq  $0x3
  4007bb:	e9 b0 ff ff ff       	jmpq   400770 <.plt>

00000000004007c0 <close@plt>:
  4007c0:	ff 25 72 08 20 00    	jmpq   *0x200872(%rip)        # 601038 <close@GLIBC_2.2.5>
  4007c6:	68 04 00 00 00       	pushq  $0x4
  4007cb:	e9 a0 ff ff ff       	jmpq   400770 <.plt>

00000000004007d0 <fprintf@plt>:
  4007d0:	ff 25 6a 08 20 00    	jmpq   *0x20086a(%rip)        # 601040 <fprintf@GLIBC_2.2.5>
  4007d6:	68 05 00 00 00       	pushq  $0x5
  4007db:	e9 90 ff ff ff       	jmpq   400770 <.plt>

00000000004007e0 <listen@plt>:
  4007e0:	ff 25 62 08 20 00    	jmpq   *0x200862(%rip)        # 601048 <listen@GLIBC_2.2.5>
  4007e6:	68 06 00 00 00       	pushq  $0x6
  4007eb:	e9 80 ff ff ff       	jmpq   400770 <.plt>

00000000004007f0 <bind@plt>:
  4007f0:	ff 25 5a 08 20 00    	jmpq   *0x20085a(%rip)        # 601050 <bind@GLIBC_2.2.5>
  4007f6:	68 07 00 00 00       	pushq  $0x7
  4007fb:	e9 70 ff ff ff       	jmpq   400770 <.plt>

0000000000400800 <perror@plt>:
  400800:	ff 25 52 08 20 00    	jmpq   *0x200852(%rip)        # 601058 <perror@GLIBC_2.2.5>
  400806:	68 08 00 00 00       	pushq  $0x8
  40080b:	e9 60 ff ff ff       	jmpq   400770 <.plt>

0000000000400810 <accept@plt>:
  400810:	ff 25 4a 08 20 00    	jmpq   *0x20084a(%rip)        # 601060 <accept@GLIBC_2.2.5>
  400816:	68 09 00 00 00       	pushq  $0x9
  40081b:	e9 50 ff ff ff       	jmpq   400770 <.plt>

0000000000400820 <exit@plt>:
  400820:	ff 25 42 08 20 00    	jmpq   *0x200842(%rip)        # 601068 <exit@GLIBC_2.2.5>
  400826:	68 0a 00 00 00       	pushq  $0xa
  40082b:	e9 40 ff ff ff       	jmpq   400770 <.plt>

0000000000400830 <fwrite@plt>:
  400830:	ff 25 3a 08 20 00    	jmpq   *0x20083a(%rip)        # 601070 <fwrite@GLIBC_2.2.5>
  400836:	68 0b 00 00 00       	pushq  $0xb
  40083b:	e9 30 ff ff ff       	jmpq   400770 <.plt>

0000000000400840 <socket@plt>:
  400840:	ff 25 32 08 20 00    	jmpq   *0x200832(%rip)        # 601078 <socket@GLIBC_2.2.5>
  400846:	68 0c 00 00 00       	pushq  $0xc
  40084b:	e9 20 ff ff ff       	jmpq   400770 <.plt>

Disassembly of section .text:

0000000000400850 <_start>:
  400850:	f3 0f 1e fa          	endbr64 
  400854:	31 ed                	xor    %ebp,%ebp
  400856:	49 89 d1             	mov    %rdx,%r9
  400859:	5e                   	pop    %rsi
  40085a:	48 89 e2             	mov    %rsp,%rdx
  40085d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  400861:	50                   	push   %rax
  400862:	54                   	push   %rsp
  400863:	49 c7 c0 80 0b 40 00 	mov    $0x400b80,%r8
  40086a:	48 c7 c1 10 0b 40 00 	mov    $0x400b10,%rcx
  400871:	48 c7 c7 cf 09 40 00 	mov    $0x4009cf,%rdi
  400878:	ff 15 6a 07 20 00    	callq  *0x20076a(%rip)        # 600fe8 <__libc_start_main@GLIBC_2.2.5>
  40087e:	f4                   	hlt    

000000000040087f <.annobin_init.c>:
  40087f:	90                   	nop

0000000000400880 <_dl_relocate_static_pie>:
  400880:	f3 0f 1e fa          	endbr64 
  400884:	c3                   	retq   

0000000000400885 <.annobin__dl_relocate_static_pie.end>:
  400885:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40088c:	00 00 00 
  40088f:	90                   	nop

0000000000400890 <deregister_tm_clones>:
  400890:	48 8d 3d f1 07 20 00 	lea    0x2007f1(%rip),%rdi        # 601088 <stdout@@GLIBC_2.2.5>
  400897:	48 8d 05 ea 07 20 00 	lea    0x2007ea(%rip),%rax        # 601088 <stdout@@GLIBC_2.2.5>
  40089e:	48 39 f8             	cmp    %rdi,%rax
  4008a1:	74 15                	je     4008b8 <deregister_tm_clones+0x28>
  4008a3:	48 8b 05 36 07 20 00 	mov    0x200736(%rip),%rax        # 600fe0 <_ITM_deregisterTMCloneTable>
  4008aa:	48 85 c0             	test   %rax,%rax
  4008ad:	74 09                	je     4008b8 <deregister_tm_clones+0x28>
  4008af:	ff e0                	jmpq   *%rax
  4008b1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  4008b8:	c3                   	retq   
  4008b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000004008c0 <register_tm_clones>:
  4008c0:	48 8d 3d c1 07 20 00 	lea    0x2007c1(%rip),%rdi        # 601088 <stdout@@GLIBC_2.2.5>
  4008c7:	48 8d 35 ba 07 20 00 	lea    0x2007ba(%rip),%rsi        # 601088 <stdout@@GLIBC_2.2.5>
  4008ce:	48 29 fe             	sub    %rdi,%rsi
  4008d1:	48 c1 fe 03          	sar    $0x3,%rsi
  4008d5:	48 89 f0             	mov    %rsi,%rax
  4008d8:	48 c1 e8 3f          	shr    $0x3f,%rax
  4008dc:	48 01 c6             	add    %rax,%rsi
  4008df:	48 d1 fe             	sar    %rsi
  4008e2:	74 14                	je     4008f8 <register_tm_clones+0x38>
  4008e4:	48 8b 05 0d 07 20 00 	mov    0x20070d(%rip),%rax        # 600ff8 <_ITM_registerTMCloneTable>
  4008eb:	48 85 c0             	test   %rax,%rax
  4008ee:	74 08                	je     4008f8 <register_tm_clones+0x38>
  4008f0:	ff e0                	jmpq   *%rax
  4008f2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  4008f8:	c3                   	retq   
  4008f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400900 <__do_global_dtors_aux>:
  400900:	f3 0f 1e fa          	endbr64 
  400904:	80 3d 85 07 20 00 00 	cmpb   $0x0,0x200785(%rip)        # 601090 <completed.7294>
  40090b:	75 13                	jne    400920 <__do_global_dtors_aux+0x20>
  40090d:	55                   	push   %rbp
  40090e:	48 89 e5             	mov    %rsp,%rbp
  400911:	e8 7a ff ff ff       	callq  400890 <deregister_tm_clones>
  400916:	c6 05 73 07 20 00 01 	movb   $0x1,0x200773(%rip)        # 601090 <completed.7294>
  40091d:	5d                   	pop    %rbp
  40091e:	c3                   	retq   
  40091f:	90                   	nop
  400920:	c3                   	retq   
  400921:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400926:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40092d:	00 00 00 

0000000000400930 <frame_dummy>:
  400930:	f3 0f 1e fa          	endbr64 
  400934:	eb 8a                	jmp    4008c0 <register_tm_clones>

0000000000400936 <die>:
  400936:	48 83 ec 18          	sub    $0x18,%rsp
  40093a:	48 89 7c 24 08       	mov    %rdi,0x8(%rsp)
  40093f:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  400944:	48 89 c7             	mov    %rax,%rdi
  400947:	e8 b4 fe ff ff       	callq  400800 <perror@plt>
  40094c:	bf 01 00 00 00       	mov    $0x1,%edi
  400951:	e8 ca fe ff ff       	callq  400820 <exit@plt>

0000000000400956 <you_hacked_me>:
  400956:	48 83 ec 08          	sub    $0x8,%rsp
  40095a:	48 8b 05 27 07 20 00 	mov    0x200727(%rip),%rax        # 601088 <stdout@@GLIBC_2.2.5>
  400961:	48 89 c1             	mov    %rax,%rcx
  400964:	ba 0f 00 00 00       	mov    $0xf,%edx
  400969:	be 01 00 00 00       	mov    $0x1,%esi
  40096e:	bf a8 0b 40 00       	mov    $0x400ba8,%edi
  400973:	e8 b8 fe ff ff       	callq  400830 <fwrite@plt>
  400978:	90                   	nop
  400979:	48 83 c4 08          	add    $0x8,%rsp
  40097d:	c3                   	retq   

000000000040097e <handle_connection>:
  40097e:	48 83 ec 28          	sub    $0x28,%rsp
  400982:	89 7c 24 0c          	mov    %edi,0xc(%rsp)
  400986:	48 8d 74 24 10       	lea    0x10(%rsp),%rsi
  40098b:	8b 44 24 0c          	mov    0xc(%rsp),%eax
  40098f:	b9 00 00 00 00       	mov    $0x0,%ecx
  400994:	ba 80 00 00 00       	mov    $0x80,%edx
  400999:	89 c7                	mov    %eax,%edi
  40099b:	e8 e0 fd ff ff       	callq  400780 <recv@plt>
  4009a0:	48 8b 05 e1 06 20 00 	mov    0x2006e1(%rip),%rax        # 601088 <stdout@@GLIBC_2.2.5>
  4009a7:	48 8d 54 24 10       	lea    0x10(%rsp),%rdx
  4009ac:	be b8 0b 40 00       	mov    $0x400bb8,%esi
  4009b1:	48 89 c7             	mov    %rax,%rdi
  4009b4:	b8 00 00 00 00       	mov    $0x0,%eax
  4009b9:	e8 12 fe ff ff       	callq  4007d0 <fprintf@plt>
  4009be:	8b 44 24 0c          	mov    0xc(%rsp),%eax
  4009c2:	89 c7                	mov    %eax,%edi
  4009c4:	e8 f7 fd ff ff       	callq  4007c0 <close@plt>
  4009c9:	90                   	nop
  4009ca:	48 83 c4 28          	add    $0x28,%rsp
  4009ce:	c3                   	retq   

00000000004009cf <main>:
  4009cf:	48 83 ec 28          	sub    $0x28,%rsp
  4009d3:	ba 00 00 00 00       	mov    $0x0,%edx
  4009d8:	be 01 00 00 00       	mov    $0x1,%esi
  4009dd:	bf 02 00 00 00       	mov    $0x2,%edi
  4009e2:	e8 59 fe ff ff       	callq  400840 <socket@plt>
  4009e7:	89 05 a7 06 20 00    	mov    %eax,0x2006a7(%rip)        # 601094 <sock.3821>
  4009ed:	8b 05 a1 06 20 00    	mov    0x2006a1(%rip),%eax        # 601094 <sock.3821>
  4009f3:	83 f8 ff             	cmp    $0xffffffff,%eax
  4009f6:	75 0a                	jne    400a02 <main+0x33>
  4009f8:	bf c0 0b 40 00       	mov    $0x400bc0,%edi
  4009fd:	e8 34 ff ff ff       	callq  400936 <die>
  400a02:	c7 44 24 1c 01 00 00 	movl   $0x1,0x1c(%rsp)
  400a09:	00 
  400a0a:	8b 05 84 06 20 00    	mov    0x200684(%rip),%eax        # 601094 <sock.3821>
  400a10:	48 8d 54 24 1c       	lea    0x1c(%rsp),%rdx
  400a15:	41 b8 04 00 00 00    	mov    $0x4,%r8d
  400a1b:	48 89 d1             	mov    %rdx,%rcx
  400a1e:	ba 02 00 00 00       	mov    $0x2,%edx
  400a23:	be 01 00 00 00       	mov    $0x1,%esi
  400a28:	89 c7                	mov    %eax,%edi
  400a2a:	e8 61 fd ff ff       	callq  400790 <setsockopt@plt>
  400a2f:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  400a33:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  400a37:	83 f8 ff             	cmp    $0xffffffff,%eax
  400a3a:	75 0a                	jne    400a46 <main+0x77>
  400a3c:	bf c7 0b 40 00       	mov    $0x400bc7,%edi
  400a41:	e8 f0 fe ff ff       	callq  400936 <die>
  400a46:	66 c7 04 24 02 00    	movw   $0x2,(%rsp)
  400a4c:	bf 11 0d 00 00       	mov    $0xd11,%edi
  400a51:	e8 4a fd ff ff       	callq  4007a0 <htons@plt>
  400a56:	66 89 44 24 02       	mov    %ax,0x2(%rsp)
  400a5b:	bf 01 00 00 7f       	mov    $0x7f000001,%edi
  400a60:	e8 4b fd ff ff       	callq  4007b0 <htonl@plt>
  400a65:	89 44 24 04          	mov    %eax,0x4(%rsp)
  400a69:	8b 05 25 06 20 00    	mov    0x200625(%rip),%eax        # 601094 <sock.3821>
  400a6f:	48 89 e1             	mov    %rsp,%rcx
  400a72:	ba 10 00 00 00       	mov    $0x10,%edx
  400a77:	48 89 ce             	mov    %rcx,%rsi
  400a7a:	89 c7                	mov    %eax,%edi
  400a7c:	e8 6f fd ff ff       	callq  4007f0 <bind@plt>
  400a81:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  400a85:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  400a89:	83 f8 ff             	cmp    $0xffffffff,%eax
  400a8c:	75 0a                	jne    400a98 <main+0xc9>
  400a8e:	bf d2 0b 40 00       	mov    $0x400bd2,%edi
  400a93:	e8 9e fe ff ff       	callq  400936 <die>
  400a98:	8b 05 f6 05 20 00    	mov    0x2005f6(%rip),%eax        # 601094 <sock.3821>
  400a9e:	be 0a 00 00 00       	mov    $0xa,%esi
  400aa3:	89 c7                	mov    %eax,%edi
  400aa5:	e8 36 fd ff ff       	callq  4007e0 <listen@plt>
  400aaa:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  400aae:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  400ab2:	83 f8 ff             	cmp    $0xffffffff,%eax
  400ab5:	75 0a                	jne    400ac1 <main+0xf2>
  400ab7:	bf d7 0b 40 00       	mov    $0x400bd7,%edi
  400abc:	e8 75 fe ff ff       	callq  400936 <die>
  400ac1:	c7 44 24 18 10 00 00 	movl   $0x10,0x18(%rsp)
  400ac8:	00 
  400ac9:	8b 05 c5 05 20 00    	mov    0x2005c5(%rip),%eax        # 601094 <sock.3821>
  400acf:	48 8d 54 24 18       	lea    0x18(%rsp),%rdx
  400ad4:	48 89 e1             	mov    %rsp,%rcx
  400ad7:	48 89 ce             	mov    %rcx,%rsi
  400ada:	89 c7                	mov    %eax,%edi
  400adc:	e8 2f fd ff ff       	callq  400810 <accept@plt>
  400ae1:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  400ae5:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  400ae9:	83 f8 ff             	cmp    $0xffffffff,%eax
  400aec:	75 0a                	jne    400af8 <main+0x129>
  400aee:	bf de 0b 40 00       	mov    $0x400bde,%edi
  400af3:	e8 3e fe ff ff       	callq  400936 <die>
  400af8:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  400afc:	89 c7                	mov    %eax,%edi
  400afe:	e8 7b fe ff ff       	callq  40097e <handle_connection>
  400b03:	eb bc                	jmp    400ac1 <main+0xf2>
  400b05:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400b0c:	00 00 00 
  400b0f:	90                   	nop

0000000000400b10 <__libc_csu_init>:
  400b10:	f3 0f 1e fa          	endbr64 
  400b14:	41 57                	push   %r15
  400b16:	49 89 d7             	mov    %rdx,%r15
  400b19:	41 56                	push   %r14
  400b1b:	49 89 f6             	mov    %rsi,%r14
  400b1e:	41 55                	push   %r13
  400b20:	41 89 fd             	mov    %edi,%r13d
  400b23:	41 54                	push   %r12
  400b25:	4c 8d 25 d4 02 20 00 	lea    0x2002d4(%rip),%r12        # 600e00 <__frame_dummy_init_array_entry>
  400b2c:	55                   	push   %rbp
  400b2d:	48 8d 2d d4 02 20 00 	lea    0x2002d4(%rip),%rbp        # 600e08 <__init_array_end>
  400b34:	53                   	push   %rbx
  400b35:	4c 29 e5             	sub    %r12,%rbp
  400b38:	48 83 ec 08          	sub    $0x8,%rsp
  400b3c:	e8 0f fc ff ff       	callq  400750 <_init>
  400b41:	48 c1 fd 03          	sar    $0x3,%rbp
  400b45:	74 1f                	je     400b66 <__libc_csu_init+0x56>
  400b47:	31 db                	xor    %ebx,%ebx
  400b49:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  400b50:	4c 89 fa             	mov    %r15,%rdx
  400b53:	4c 89 f6             	mov    %r14,%rsi
  400b56:	44 89 ef             	mov    %r13d,%edi
  400b59:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  400b5d:	48 83 c3 01          	add    $0x1,%rbx
  400b61:	48 39 dd             	cmp    %rbx,%rbp
  400b64:	75 ea                	jne    400b50 <__libc_csu_init+0x40>
  400b66:	48 83 c4 08          	add    $0x8,%rsp
  400b6a:	5b                   	pop    %rbx
  400b6b:	5d                   	pop    %rbp
  400b6c:	41 5c                	pop    %r12
  400b6e:	41 5d                	pop    %r13
  400b70:	41 5e                	pop    %r14
  400b72:	41 5f                	pop    %r15
  400b74:	c3                   	retq   

0000000000400b75 <.annobin___libc_csu_fini.start>:
  400b75:	66 66 2e 0f 1f 84 00 	data16 nopw %cs:0x0(%rax,%rax,1)
  400b7c:	00 00 00 00 

0000000000400b80 <__libc_csu_fini>:
  400b80:	f3 0f 1e fa          	endbr64 
  400b84:	c3                   	retq   

Disassembly of section .fini:

0000000000400b88 <_fini>:
  400b88:	f3 0f 1e fa          	endbr64 
  400b8c:	48 83 ec 08          	sub    $0x8,%rsp
  400b90:	48 83 c4 08          	add    $0x8,%rsp
  400b94:	c3                   	retq   
