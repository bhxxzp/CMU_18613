
bomb：     文件格式 elf64-x86-64


Disassembly of section .init:

0000000000400cb0 <_init>:
  400cb0:	48 83 ec 08          	sub    $0x8,%rsp
  400cb4:	48 8b 05 3d 33 20 00 	mov    0x20333d(%rip),%rax        # 603ff8 <__gmon_start__>
  400cbb:	48 85 c0             	test   %rax,%rax
  400cbe:	74 05                	je     400cc5 <_init+0x15>
  400cc0:	e8 5b 00 00 00       	callq  400d20 <__gmon_start__@plt>
  400cc5:	48 83 c4 08          	add    $0x8,%rsp
  400cc9:	c3                   	retq   

Disassembly of section .plt:

0000000000400cd0 <.plt>:
  400cd0:	ff 35 32 33 20 00    	pushq  0x203332(%rip)        # 604008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400cd6:	ff 25 34 33 20 00    	jmpq   *0x203334(%rip)        # 604010 <_GLOBAL_OFFSET_TABLE_+0x10>
  400cdc:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400ce0 <printf@plt>:
  400ce0:	ff 25 32 33 20 00    	jmpq   *0x203332(%rip)        # 604018 <printf@GLIBC_2.2.5>
  400ce6:	68 00 00 00 00       	pushq  $0x0
  400ceb:	e9 e0 ff ff ff       	jmpq   400cd0 <.plt>

0000000000400cf0 <snprintf@plt>:
  400cf0:	ff 25 2a 33 20 00    	jmpq   *0x20332a(%rip)        # 604020 <snprintf@GLIBC_2.2.5>
  400cf6:	68 01 00 00 00       	pushq  $0x1
  400cfb:	e9 d0 ff ff ff       	jmpq   400cd0 <.plt>

0000000000400d00 <close@plt>:
  400d00:	ff 25 22 33 20 00    	jmpq   *0x203322(%rip)        # 604028 <close@GLIBC_2.2.5>
  400d06:	68 02 00 00 00       	pushq  $0x2
  400d0b:	e9 c0 ff ff ff       	jmpq   400cd0 <.plt>

0000000000400d10 <gethostbyname@plt>:
  400d10:	ff 25 1a 33 20 00    	jmpq   *0x20331a(%rip)        # 604030 <gethostbyname@GLIBC_2.2.5>
  400d16:	68 03 00 00 00       	pushq  $0x3
  400d1b:	e9 b0 ff ff ff       	jmpq   400cd0 <.plt>

0000000000400d20 <__gmon_start__@plt>:
  400d20:	ff 25 12 33 20 00    	jmpq   *0x203312(%rip)        # 604038 <__gmon_start__>
  400d26:	68 04 00 00 00       	pushq  $0x4
  400d2b:	e9 a0 ff ff ff       	jmpq   400cd0 <.plt>

0000000000400d30 <puts@plt>:
  400d30:	ff 25 0a 33 20 00    	jmpq   *0x20330a(%rip)        # 604040 <puts@GLIBC_2.2.5>
  400d36:	68 05 00 00 00       	pushq  $0x5
  400d3b:	e9 90 ff ff ff       	jmpq   400cd0 <.plt>

0000000000400d40 <__isoc99_sscanf@plt>:
  400d40:	ff 25 02 33 20 00    	jmpq   *0x203302(%rip)        # 604048 <__isoc99_sscanf@GLIBC_2.7>
  400d46:	68 06 00 00 00       	pushq  $0x6
  400d4b:	e9 80 ff ff ff       	jmpq   400cd0 <.plt>

0000000000400d50 <exit@plt>:
  400d50:	ff 25 fa 32 20 00    	jmpq   *0x2032fa(%rip)        # 604050 <exit@GLIBC_2.2.5>
  400d56:	68 07 00 00 00       	pushq  $0x7
  400d5b:	e9 70 ff ff ff       	jmpq   400cd0 <.plt>

0000000000400d60 <strcasecmp@plt>:
  400d60:	ff 25 f2 32 20 00    	jmpq   *0x2032f2(%rip)        # 604058 <strcasecmp@GLIBC_2.2.5>
  400d66:	68 08 00 00 00       	pushq  $0x8
  400d6b:	e9 60 ff ff ff       	jmpq   400cd0 <.plt>

0000000000400d70 <read@plt>:
  400d70:	ff 25 ea 32 20 00    	jmpq   *0x2032ea(%rip)        # 604060 <read@GLIBC_2.2.5>
  400d76:	68 09 00 00 00       	pushq  $0x9
  400d7b:	e9 50 ff ff ff       	jmpq   400cd0 <.plt>

0000000000400d80 <fopen@plt>:
  400d80:	ff 25 e2 32 20 00    	jmpq   *0x2032e2(%rip)        # 604068 <fopen@GLIBC_2.2.5>
  400d86:	68 0a 00 00 00       	pushq  $0xa
  400d8b:	e9 40 ff ff ff       	jmpq   400cd0 <.plt>

0000000000400d90 <__libc_start_main@plt>:
  400d90:	ff 25 da 32 20 00    	jmpq   *0x2032da(%rip)        # 604070 <__libc_start_main@GLIBC_2.2.5>
  400d96:	68 0b 00 00 00       	pushq  $0xb
  400d9b:	e9 30 ff ff ff       	jmpq   400cd0 <.plt>

0000000000400da0 <fgets@plt>:
  400da0:	ff 25 d2 32 20 00    	jmpq   *0x2032d2(%rip)        # 604078 <fgets@GLIBC_2.2.5>
  400da6:	68 0c 00 00 00       	pushq  $0xc
  400dab:	e9 20 ff ff ff       	jmpq   400cd0 <.plt>

0000000000400db0 <creat@plt>:
  400db0:	ff 25 ca 32 20 00    	jmpq   *0x2032ca(%rip)        # 604080 <creat@GLIBC_2.2.5>
  400db6:	68 0d 00 00 00       	pushq  $0xd
  400dbb:	e9 10 ff ff ff       	jmpq   400cd0 <.plt>

0000000000400dc0 <bcopy@plt>:
  400dc0:	ff 25 c2 32 20 00    	jmpq   *0x2032c2(%rip)        # 604088 <bcopy@GLIBC_2.2.5>
  400dc6:	68 0e 00 00 00       	pushq  $0xe
  400dcb:	e9 00 ff ff ff       	jmpq   400cd0 <.plt>

0000000000400dd0 <__xstat@plt>:
  400dd0:	ff 25 ba 32 20 00    	jmpq   *0x2032ba(%rip)        # 604090 <__xstat@GLIBC_2.2.5>
  400dd6:	68 0f 00 00 00       	pushq  $0xf
  400ddb:	e9 f0 fe ff ff       	jmpq   400cd0 <.plt>

0000000000400de0 <__ctype_b_loc@plt>:
  400de0:	ff 25 b2 32 20 00    	jmpq   *0x2032b2(%rip)        # 604098 <__ctype_b_loc@GLIBC_2.3>
  400de6:	68 10 00 00 00       	pushq  $0x10
  400deb:	e9 e0 fe ff ff       	jmpq   400cd0 <.plt>

0000000000400df0 <sprintf@plt>:
  400df0:	ff 25 aa 32 20 00    	jmpq   *0x2032aa(%rip)        # 6040a0 <sprintf@GLIBC_2.2.5>
  400df6:	68 11 00 00 00       	pushq  $0x11
  400dfb:	e9 d0 fe ff ff       	jmpq   400cd0 <.plt>

0000000000400e00 <sleep@plt>:
  400e00:	ff 25 a2 32 20 00    	jmpq   *0x2032a2(%rip)        # 6040a8 <sleep@GLIBC_2.2.5>
  400e06:	68 12 00 00 00       	pushq  $0x12
  400e0b:	e9 c0 fe ff ff       	jmpq   400cd0 <.plt>

0000000000400e10 <connect@plt>:
  400e10:	ff 25 9a 32 20 00    	jmpq   *0x20329a(%rip)        # 6040b0 <connect@GLIBC_2.2.5>
  400e16:	68 13 00 00 00       	pushq  $0x13
  400e1b:	e9 b0 fe ff ff       	jmpq   400cd0 <.plt>

0000000000400e20 <gethostname@plt>:
  400e20:	ff 25 92 32 20 00    	jmpq   *0x203292(%rip)        # 6040b8 <gethostname@GLIBC_2.2.5>
  400e26:	68 14 00 00 00       	pushq  $0x14
  400e2b:	e9 a0 fe ff ff       	jmpq   400cd0 <.plt>

0000000000400e30 <clock_nanosleep@plt>:
  400e30:	ff 25 8a 32 20 00    	jmpq   *0x20328a(%rip)        # 6040c0 <clock_nanosleep@GLIBC_2.17>
  400e36:	68 15 00 00 00       	pushq  $0x15
  400e3b:	e9 90 fe ff ff       	jmpq   400cd0 <.plt>

0000000000400e40 <signal@plt>:
  400e40:	ff 25 82 32 20 00    	jmpq   *0x203282(%rip)        # 6040c8 <signal@GLIBC_2.2.5>
  400e46:	68 16 00 00 00       	pushq  $0x16
  400e4b:	e9 80 fe ff ff       	jmpq   400cd0 <.plt>

0000000000400e50 <socket@plt>:
  400e50:	ff 25 7a 32 20 00    	jmpq   *0x20327a(%rip)        # 6040d0 <socket@GLIBC_2.2.5>
  400e56:	68 17 00 00 00       	pushq  $0x17
  400e5b:	e9 70 fe ff ff       	jmpq   400cd0 <.plt>

0000000000400e60 <getenv@plt>:
  400e60:	ff 25 72 32 20 00    	jmpq   *0x203272(%rip)        # 6040d8 <getenv@GLIBC_2.2.5>
  400e66:	68 18 00 00 00       	pushq  $0x18
  400e6b:	e9 60 fe ff ff       	jmpq   400cd0 <.plt>

0000000000400e70 <alarm@plt>:
  400e70:	ff 25 6a 32 20 00    	jmpq   *0x20326a(%rip)        # 6040e0 <alarm@GLIBC_2.2.5>
  400e76:	68 19 00 00 00       	pushq  $0x19
  400e7b:	e9 50 fe ff ff       	jmpq   400cd0 <.plt>

0000000000400e80 <__errno_location@plt>:
  400e80:	ff 25 62 32 20 00    	jmpq   *0x203262(%rip)        # 6040e8 <__errno_location@GLIBC_2.2.5>
  400e86:	68 1a 00 00 00       	pushq  $0x1a
  400e8b:	e9 40 fe ff ff       	jmpq   400cd0 <.plt>

0000000000400e90 <strcpy@plt>:
  400e90:	ff 25 5a 32 20 00    	jmpq   *0x20325a(%rip)        # 6040f0 <strcpy@GLIBC_2.2.5>
  400e96:	68 1b 00 00 00       	pushq  $0x1b
  400e9b:	e9 30 fe ff ff       	jmpq   400cd0 <.plt>

0000000000400ea0 <fwrite@plt>:
  400ea0:	ff 25 52 32 20 00    	jmpq   *0x203252(%rip)        # 6040f8 <fwrite@GLIBC_2.2.5>
  400ea6:	68 1c 00 00 00       	pushq  $0x1c
  400eab:	e9 20 fe ff ff       	jmpq   400cd0 <.plt>

0000000000400eb0 <perror@plt>:
  400eb0:	ff 25 4a 32 20 00    	jmpq   *0x20324a(%rip)        # 604100 <perror@GLIBC_2.2.5>
  400eb6:	68 1d 00 00 00       	pushq  $0x1d
  400ebb:	e9 10 fe ff ff       	jmpq   400cd0 <.plt>

0000000000400ec0 <write@plt>:
  400ec0:	ff 25 42 32 20 00    	jmpq   *0x203242(%rip)        # 604108 <write@GLIBC_2.2.5>
  400ec6:	68 1e 00 00 00       	pushq  $0x1e
  400ecb:	e9 00 fe ff ff       	jmpq   400cd0 <.plt>

0000000000400ed0 <memcpy@plt>:
  400ed0:	ff 25 3a 32 20 00    	jmpq   *0x20323a(%rip)        # 604110 <memcpy@GLIBC_2.14>
  400ed6:	68 1f 00 00 00       	pushq  $0x1f
  400edb:	e9 f0 fd ff ff       	jmpq   400cd0 <.plt>

0000000000400ee0 <open@plt>:
  400ee0:	ff 25 32 32 20 00    	jmpq   *0x203232(%rip)        # 604118 <open@GLIBC_2.2.5>
  400ee6:	68 20 00 00 00       	pushq  $0x20
  400eeb:	e9 e0 fd ff ff       	jmpq   400cd0 <.plt>

0000000000400ef0 <mkdir@plt>:
  400ef0:	ff 25 2a 32 20 00    	jmpq   *0x20322a(%rip)        # 604120 <mkdir@GLIBC_2.2.5>
  400ef6:	68 21 00 00 00       	pushq  $0x21
  400efb:	e9 d0 fd ff ff       	jmpq   400cd0 <.plt>

0000000000400f00 <fflush@plt>:
  400f00:	ff 25 22 32 20 00    	jmpq   *0x203222(%rip)        # 604128 <fflush@GLIBC_2.2.5>
  400f06:	68 22 00 00 00       	pushq  $0x22
  400f0b:	e9 c0 fd ff ff       	jmpq   400cd0 <.plt>

Disassembly of section .text:

0000000000400f10 <_start>:
  400f10:	31 ed                	xor    %ebp,%ebp
  400f12:	49 89 d1             	mov    %rdx,%r9
  400f15:	5e                   	pop    %rsi
  400f16:	48 89 e2             	mov    %rsp,%rdx
  400f19:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  400f1d:	50                   	push   %rax
  400f1e:	54                   	push   %rsp
  400f1f:	49 c7 c0 b0 2a 40 00 	mov    $0x402ab0,%r8
  400f26:	48 c7 c1 40 2a 40 00 	mov    $0x402a40,%rcx
  400f2d:	48 c7 c7 fd 0f 40 00 	mov    $0x400ffd,%rdi
  400f34:	e8 57 fe ff ff       	callq  400d90 <__libc_start_main@plt>
  400f39:	f4                   	hlt    
  400f3a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400f40 <deregister_tm_clones>:
  400f40:	b8 67 58 60 00       	mov    $0x605867,%eax
  400f45:	55                   	push   %rbp
  400f46:	48 2d 60 58 60 00    	sub    $0x605860,%rax
  400f4c:	48 83 f8 0e          	cmp    $0xe,%rax
  400f50:	48 89 e5             	mov    %rsp,%rbp
  400f53:	77 02                	ja     400f57 <deregister_tm_clones+0x17>
  400f55:	5d                   	pop    %rbp
  400f56:	c3                   	retq   
  400f57:	b8 00 00 00 00       	mov    $0x0,%eax
  400f5c:	48 85 c0             	test   %rax,%rax
  400f5f:	74 f4                	je     400f55 <deregister_tm_clones+0x15>
  400f61:	5d                   	pop    %rbp
  400f62:	bf 60 58 60 00       	mov    $0x605860,%edi
  400f67:	ff e0                	jmpq   *%rax
  400f69:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400f70 <register_tm_clones>:
  400f70:	b8 60 58 60 00       	mov    $0x605860,%eax
  400f75:	55                   	push   %rbp
  400f76:	48 2d 60 58 60 00    	sub    $0x605860,%rax
  400f7c:	48 c1 f8 03          	sar    $0x3,%rax
  400f80:	48 89 e5             	mov    %rsp,%rbp
  400f83:	48 89 c2             	mov    %rax,%rdx
  400f86:	48 c1 ea 3f          	shr    $0x3f,%rdx
  400f8a:	48 01 d0             	add    %rdx,%rax
  400f8d:	48 d1 f8             	sar    %rax
  400f90:	75 02                	jne    400f94 <register_tm_clones+0x24>
  400f92:	5d                   	pop    %rbp
  400f93:	c3                   	retq   
  400f94:	ba 00 00 00 00       	mov    $0x0,%edx
  400f99:	48 85 d2             	test   %rdx,%rdx
  400f9c:	74 f4                	je     400f92 <register_tm_clones+0x22>
  400f9e:	5d                   	pop    %rbp
  400f9f:	48 89 c6             	mov    %rax,%rsi
  400fa2:	bf 60 58 60 00       	mov    $0x605860,%edi
  400fa7:	ff e2                	jmpq   *%rdx
  400fa9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400fb0 <__do_global_dtors_aux>:
  400fb0:	80 3d c1 48 20 00 00 	cmpb   $0x0,0x2048c1(%rip)        # 605878 <completed.6355>
  400fb7:	75 11                	jne    400fca <__do_global_dtors_aux+0x1a>
  400fb9:	55                   	push   %rbp
  400fba:	48 89 e5             	mov    %rsp,%rbp
  400fbd:	e8 7e ff ff ff       	callq  400f40 <deregister_tm_clones>
  400fc2:	5d                   	pop    %rbp
  400fc3:	c6 05 ae 48 20 00 01 	movb   $0x1,0x2048ae(%rip)        # 605878 <completed.6355>
  400fca:	f3 c3                	repz retq 
  400fcc:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400fd0 <frame_dummy>:
  400fd0:	48 83 3d 28 2e 20 00 	cmpq   $0x0,0x202e28(%rip)        # 603e00 <__JCR_END__>
  400fd7:	00 
  400fd8:	74 1e                	je     400ff8 <frame_dummy+0x28>
  400fda:	b8 00 00 00 00       	mov    $0x0,%eax
  400fdf:	48 85 c0             	test   %rax,%rax
  400fe2:	74 14                	je     400ff8 <frame_dummy+0x28>
  400fe4:	55                   	push   %rbp
  400fe5:	bf 00 3e 60 00       	mov    $0x603e00,%edi
  400fea:	48 89 e5             	mov    %rsp,%rbp
  400fed:	ff d0                	callq  *%rax
  400fef:	5d                   	pop    %rbp
  400ff0:	e9 7b ff ff ff       	jmpq   400f70 <register_tm_clones>
  400ff5:	0f 1f 00             	nopl   (%rax)
  400ff8:	e9 73 ff ff ff       	jmpq   400f70 <register_tm_clones>

0000000000400ffd <main>:
  400ffd:	53                   	push   %rbx
  400ffe:	83 ff 01             	cmp    $0x1,%edi
  401001:	75 10                	jne    401013 <main+0x16>
  401003:	48 8b 05 56 48 20 00 	mov    0x204856(%rip),%rax        # 605860 <stdin@@GLIBC_2.2.5>
  40100a:	48 89 05 7f 48 20 00 	mov    %rax,0x20487f(%rip)        # 605890 <infile>
  401011:	eb 59                	jmp    40106c <main+0x6f>
  401013:	48 89 f3             	mov    %rsi,%rbx
  401016:	83 ff 02             	cmp    $0x2,%edi
  401019:	75 35                	jne    401050 <main+0x53>
  40101b:	48 8b 7e 08          	mov    0x8(%rsi),%rdi
  40101f:	be 62 30 40 00       	mov    $0x403062,%esi
  401024:	e8 57 fd ff ff       	callq  400d80 <fopen@plt>
  401029:	48 89 05 60 48 20 00 	mov    %rax,0x204860(%rip)        # 605890 <infile>
  401030:	48 85 c0             	test   %rax,%rax
  401033:	75 37                	jne    40106c <main+0x6f>
  401035:	48 8b 53 08          	mov    0x8(%rbx),%rdx
  401039:	48 8b 33             	mov    (%rbx),%rsi
  40103c:	bf d0 2a 40 00       	mov    $0x402ad0,%edi
  401041:	e8 9a fc ff ff       	callq  400ce0 <printf@plt>
  401046:	bf 08 00 00 00       	mov    $0x8,%edi
  40104b:	e8 00 fd ff ff       	callq  400d50 <exit@plt>
  401050:	48 8b 36             	mov    (%rsi),%rsi
  401053:	bf ed 2a 40 00       	mov    $0x402aed,%edi
  401058:	b8 00 00 00 00       	mov    $0x0,%eax
  40105d:	e8 7e fc ff ff       	callq  400ce0 <printf@plt>
  401062:	bf 08 00 00 00       	mov    $0x8,%edi
  401067:	e8 e4 fc ff ff       	callq  400d50 <exit@plt>
  40106c:	e8 89 0c 00 00       	callq  401cfa <initialize_bomb>
  401071:	bf 58 2b 40 00       	mov    $0x402b58,%edi
  401076:	e8 b5 fc ff ff       	callq  400d30 <puts@plt>
  40107b:	bf 98 2b 40 00       	mov    $0x402b98,%edi
  401080:	e8 ab fc ff ff       	callq  400d30 <puts@plt>
  401085:	e8 7d 0a 00 00       	callq  401b07 <read_line>
  40108a:	48 89 c7             	mov    %rax,%rdi
  40108d:	e8 9e 00 00 00       	callq  401130 <phase_1>
  401092:	e8 b9 0b 00 00       	callq  401c50 <phase_defused>
  401097:	bf c8 2b 40 00       	mov    $0x402bc8,%edi
  40109c:	e8 8f fc ff ff       	callq  400d30 <puts@plt>
  4010a1:	e8 61 0a 00 00       	callq  401b07 <read_line>
  4010a6:	48 89 c7             	mov    %rax,%rdi
  4010a9:	e8 9e 00 00 00       	callq  40114c <phase_2>
  4010ae:	e8 9d 0b 00 00       	callq  401c50 <phase_defused>
  4010b3:	bf 07 2b 40 00       	mov    $0x402b07,%edi
  4010b8:	e8 73 fc ff ff       	callq  400d30 <puts@plt>
  4010bd:	e8 45 0a 00 00       	callq  401b07 <read_line>
  4010c2:	48 89 c7             	mov    %rax,%rdi
  4010c5:	e8 cf 00 00 00       	callq  401199 <phase_3>
  4010ca:	e8 81 0b 00 00       	callq  401c50 <phase_defused>
  4010cf:	bf 25 2b 40 00       	mov    $0x402b25,%edi
  4010d4:	e8 57 fc ff ff       	callq  400d30 <puts@plt>
  4010d9:	e8 29 0a 00 00       	callq  401b07 <read_line>
  4010de:	48 89 c7             	mov    %rax,%rdi
  4010e1:	e8 58 02 00 00       	callq  40133e <phase_4>
  4010e6:	e8 65 0b 00 00       	callq  401c50 <phase_defused>
  4010eb:	bf f8 2b 40 00       	mov    $0x402bf8,%edi
  4010f0:	e8 3b fc ff ff       	callq  400d30 <puts@plt>
  4010f5:	e8 0d 0a 00 00       	callq  401b07 <read_line>
  4010fa:	48 89 c7             	mov    %rax,%rdi
  4010fd:	e8 9c 02 00 00       	callq  40139e <phase_5>
  401102:	e8 49 0b 00 00       	callq  401c50 <phase_defused>
  401107:	bf 34 2b 40 00       	mov    $0x402b34,%edi
  40110c:	e8 1f fc ff ff       	callq  400d30 <puts@plt>
  401111:	e8 f1 09 00 00       	callq  401b07 <read_line>
  401116:	48 89 c7             	mov    %rax,%rdi
  401119:	e8 db 02 00 00       	callq  4013f9 <phase_6>
  40111e:	e8 2d 0b 00 00       	callq  401c50 <phase_defused>
  401123:	b8 00 00 00 00       	mov    $0x0,%eax
  401128:	5b                   	pop    %rbx
  401129:	c3                   	retq   
  40112a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000401130 <phase_1>:
  401130:	48 83 ec 08          	sub    $0x8,%rsp
  401134:	be e0 44 60 00       	mov    $0x6044e0,%esi
  401139:	e8 3c 07 00 00       	callq  40187a <strings_not_equal>
  40113e:	84 c0                	test   %al,%al
  401140:	74 05                	je     401147 <phase_1+0x17>
  401142:	e8 48 09 00 00       	callq  401a8f <explode_bomb>
  401147:	48 83 c4 08          	add    $0x8,%rsp
  40114b:	c3                   	retq   

000000000040114c <phase_2>:
  40114c:	53                   	push   %rbx
  40114d:	48 83 ec 30          	sub    $0x30,%rsp
  401151:	48 89 e6             	mov    %rsp,%rsi
  401154:	e8 6c 09 00 00       	callq  401ac5 <read_six_numbers>
  401159:	48 83 3c 24 03       	cmpq   $0x3,(%rsp)
  40115e:	75 08                	jne    401168 <phase_2+0x1c>
  401160:	48 83 7c 24 08 03    	cmpq   $0x3,0x8(%rsp)
  401166:	74 05                	je     40116d <phase_2+0x21>
  401168:	e8 22 09 00 00       	callq  401a8f <explode_bomb>
  40116d:	bb 02 00 00 00       	mov    $0x2,%ebx
  401172:	eb 19                	jmp    40118d <phase_2+0x41>
  401174:	48 8b 44 dc f8       	mov    -0x8(%rsp,%rbx,8),%rax
  401179:	48 03 44 dc f0       	add    -0x10(%rsp,%rbx,8),%rax
  40117e:	48 39 04 dc          	cmp    %rax,(%rsp,%rbx,8)
  401182:	74 05                	je     401189 <phase_2+0x3d>
  401184:	e8 06 09 00 00       	callq  401a8f <explode_bomb>
  401189:	48 83 c3 01          	add    $0x1,%rbx
  40118d:	48 83 fb 05          	cmp    $0x5,%rbx
  401191:	76 e1                	jbe    401174 <phase_2+0x28>
  401193:	48 83 c4 30          	add    $0x30,%rsp
  401197:	5b                   	pop    %rbx
  401198:	c3                   	retq   

0000000000401199 <phase_3>:
  401199:	48 83 ec 28          	sub    $0x28,%rsp
  40119d:	4c 8d 44 24 10       	lea    0x10(%rsp),%r8
  4011a2:	48 8d 4c 24 0f       	lea    0xf(%rsp),%rcx
  4011a7:	48 8d 54 24 18       	lea    0x18(%rsp),%rdx
  4011ac:	be 1c 2c 40 00       	mov    $0x402c1c,%esi
  4011b1:	b8 00 00 00 00       	mov    $0x0,%eax
  4011b6:	e8 85 fb ff ff       	callq  400d40 <__isoc99_sscanf@plt>
  4011bb:	83 f8 02             	cmp    $0x2,%eax
  4011be:	7f 05                	jg     4011c5 <phase_3+0x2c>
  4011c0:	e8 ca 08 00 00       	callq  401a8f <explode_bomb>
  4011c5:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  4011ca:	48 83 e8 05          	sub    $0x5,%rax
  4011ce:	48 83 f8 07          	cmp    $0x7,%rax
  4011d2:	0f 87 c8 00 00 00    	ja     4012a0 <phase_3+0x107>
  4011d8:	ff 24 c5 30 2c 40 00 	jmpq   *0x402c30(,%rax,8)
  4011df:	48 83 7c 24 10 4f    	cmpq   $0x4f,0x10(%rsp)
  4011e5:	0f 84 c1 00 00 00    	je     4012ac <phase_3+0x113>
  4011eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  4011f0:	e8 9a 08 00 00       	callq  401a8f <explode_bomb>
  4011f5:	b8 64 00 00 00       	mov    $0x64,%eax
  4011fa:	e9 e3 00 00 00       	jmpq   4012e2 <phase_3+0x149>
  4011ff:	48 83 7c 24 10 37    	cmpq   $0x37,0x10(%rsp)
  401205:	0f 84 a8 00 00 00    	je     4012b3 <phase_3+0x11a>
  40120b:	e8 7f 08 00 00       	callq  401a8f <explode_bomb>
  401210:	b8 64 00 00 00       	mov    $0x64,%eax
  401215:	e9 c8 00 00 00       	jmpq   4012e2 <phase_3+0x149>
  40121a:	48 83 7c 24 10 25    	cmpq   $0x25,0x10(%rsp)
  401220:	0f 84 94 00 00 00    	je     4012ba <phase_3+0x121>
  401226:	e8 64 08 00 00       	callq  401a8f <explode_bomb>
  40122b:	b8 6b 00 00 00       	mov    $0x6b,%eax
  401230:	e9 ad 00 00 00       	jmpq   4012e2 <phase_3+0x149>
  401235:	48 83 7c 24 10 78    	cmpq   $0x78,0x10(%rsp)
  40123b:	0f 84 80 00 00 00    	je     4012c1 <phase_3+0x128>
  401241:	e8 49 08 00 00       	callq  401a8f <explode_bomb>
  401246:	b8 68 00 00 00       	mov    $0x68,%eax
  40124b:	e9 92 00 00 00       	jmpq   4012e2 <phase_3+0x149>
  401250:	48 83 7c 24 10 40    	cmpq   $0x40,0x10(%rsp)
  401256:	74 70                	je     4012c8 <phase_3+0x12f>
  401258:	e8 32 08 00 00       	callq  401a8f <explode_bomb>
  40125d:	b8 64 00 00 00       	mov    $0x64,%eax
  401262:	eb 7e                	jmp    4012e2 <phase_3+0x149>
  401264:	48 83 7c 24 10 33    	cmpq   $0x33,0x10(%rsp)
  40126a:	74 63                	je     4012cf <phase_3+0x136>
  40126c:	e8 1e 08 00 00       	callq  401a8f <explode_bomb>
  401271:	b8 70 00 00 00       	mov    $0x70,%eax
  401276:	eb 6a                	jmp    4012e2 <phase_3+0x149>
  401278:	48 83 7c 24 10 33    	cmpq   $0x33,0x10(%rsp)
  40127e:	74 56                	je     4012d6 <phase_3+0x13d>
  401280:	e8 0a 08 00 00       	callq  401a8f <explode_bomb>
  401285:	b8 6b 00 00 00       	mov    $0x6b,%eax
  40128a:	eb 56                	jmp    4012e2 <phase_3+0x149>
  40128c:	48 83 7c 24 10 4e    	cmpq   $0x4e,0x10(%rsp)
  401292:	74 49                	je     4012dd <phase_3+0x144>
  401294:	e8 f6 07 00 00       	callq  401a8f <explode_bomb>
  401299:	b8 70 00 00 00       	mov    $0x70,%eax
  40129e:	eb 42                	jmp    4012e2 <phase_3+0x149>
  4012a0:	e8 ea 07 00 00       	callq  401a8f <explode_bomb>
  4012a5:	b8 64 00 00 00       	mov    $0x64,%eax
  4012aa:	eb 36                	jmp    4012e2 <phase_3+0x149>
  4012ac:	b8 64 00 00 00       	mov    $0x64,%eax
  4012b1:	eb 2f                	jmp    4012e2 <phase_3+0x149>
  4012b3:	b8 64 00 00 00       	mov    $0x64,%eax
  4012b8:	eb 28                	jmp    4012e2 <phase_3+0x149>
  4012ba:	b8 6b 00 00 00       	mov    $0x6b,%eax
  4012bf:	eb 21                	jmp    4012e2 <phase_3+0x149>
  4012c1:	b8 68 00 00 00       	mov    $0x68,%eax
  4012c6:	eb 1a                	jmp    4012e2 <phase_3+0x149>
  4012c8:	b8 64 00 00 00       	mov    $0x64,%eax
  4012cd:	eb 13                	jmp    4012e2 <phase_3+0x149>
  4012cf:	b8 70 00 00 00       	mov    $0x70,%eax
  4012d4:	eb 0c                	jmp    4012e2 <phase_3+0x149>
  4012d6:	b8 6b 00 00 00       	mov    $0x6b,%eax
  4012db:	eb 05                	jmp    4012e2 <phase_3+0x149>
  4012dd:	b8 70 00 00 00       	mov    $0x70,%eax
  4012e2:	3a 44 24 0f          	cmp    0xf(%rsp),%al
  4012e6:	74 05                	je     4012ed <phase_3+0x154>
  4012e8:	e8 a2 07 00 00       	callq  401a8f <explode_bomb>
  4012ed:	48 83 c4 28          	add    $0x28,%rsp
  4012f1:	c3                   	retq   

00000000004012f2 <func4>:
  4012f2:	48 83 ec 08          	sub    $0x8,%rsp
  4012f6:	48 89 d0             	mov    %rdx,%rax
  4012f9:	48 29 f0             	sub    %rsi,%rax
  4012fc:	48 89 c1             	mov    %rax,%rcx
  4012ff:	48 c1 e9 3f          	shr    $0x3f,%rcx
  401303:	48 01 c8             	add    %rcx,%rax
  401306:	48 d1 f8             	sar    %rax
  401309:	48 01 f0             	add    %rsi,%rax
  40130c:	48 39 f8             	cmp    %rdi,%rax
  40130f:	7e 0e                	jle    40131f <func4+0x2d>
  401311:	48 8d 50 ff          	lea    -0x1(%rax),%rdx
  401315:	e8 d8 ff ff ff       	callq  4012f2 <func4>
  40131a:	48 01 c0             	add    %rax,%rax
  40131d:	eb 1a                	jmp    401339 <func4+0x47>
  40131f:	48 39 f8             	cmp    %rdi,%rax
  401322:	7d 10                	jge    401334 <func4+0x42>
  401324:	48 8d 70 01          	lea    0x1(%rax),%rsi
  401328:	e8 c5 ff ff ff       	callq  4012f2 <func4>
  40132d:	48 8d 44 00 01       	lea    0x1(%rax,%rax,1),%rax
  401332:	eb 05                	jmp    401339 <func4+0x47>
  401334:	b8 00 00 00 00       	mov    $0x0,%eax
  401339:	48 83 c4 08          	add    $0x8,%rsp
  40133d:	c3                   	retq   

000000000040133e <phase_4>:
  40133e:	48 83 ec 18          	sub    $0x18,%rsp
  401342:	48 89 e1             	mov    %rsp,%rcx
  401345:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
  40134a:	be f8 30 40 00       	mov    $0x4030f8,%esi
  40134f:	b8 00 00 00 00       	mov    $0x0,%eax
  401354:	e8 e7 f9 ff ff       	callq  400d40 <__isoc99_sscanf@plt>
  401359:	83 f8 02             	cmp    $0x2,%eax
  40135c:	75 10                	jne    40136e <phase_4+0x30>
  40135e:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  401363:	48 85 c0             	test   %rax,%rax
  401366:	78 06                	js     40136e <phase_4+0x30>
  401368:	48 83 f8 0e          	cmp    $0xe,%rax
  40136c:	7e 05                	jle    401373 <phase_4+0x35>
  40136e:	e8 1c 07 00 00       	callq  401a8f <explode_bomb>
  401373:	ba 0e 00 00 00       	mov    $0xe,%edx
  401378:	be 00 00 00 00       	mov    $0x0,%esi
  40137d:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
  401382:	e8 6b ff ff ff       	callq  4012f2 <func4>
  401387:	48 83 f8 05          	cmp    $0x5,%rax
  40138b:	75 07                	jne    401394 <phase_4+0x56>
  40138d:	48 83 3c 24 05       	cmpq   $0x5,(%rsp)
  401392:	74 05                	je     401399 <phase_4+0x5b>
  401394:	e8 f6 06 00 00       	callq  401a8f <explode_bomb>
  401399:	48 83 c4 18          	add    $0x18,%rsp
  40139d:	c3                   	retq   

000000000040139e <phase_5>:
  40139e:	53                   	push   %rbx
  40139f:	48 83 ec 10          	sub    $0x10,%rsp
  4013a3:	48 89 fb             	mov    %rdi,%rbx
  4013a6:	e8 b9 04 00 00       	callq  401864 <string_length>
  4013ab:	48 83 f8 06          	cmp    $0x6,%rax
  4013af:	74 05                	je     4013b6 <phase_5+0x18>
  4013b1:	e8 d9 06 00 00       	callq  401a8f <explode_bomb>
  4013b6:	b8 00 00 00 00       	mov    $0x0,%eax
  4013bb:	eb 15                	jmp    4013d2 <phase_5+0x34>
  4013bd:	0f b6 14 03          	movzbl (%rbx,%rax,1),%edx
  4013c1:	83 e2 0f             	and    $0xf,%edx
  4013c4:	0f b6 92 70 2c 40 00 	movzbl 0x402c70(%rdx),%edx
  4013cb:	88 14 04             	mov    %dl,(%rsp,%rax,1)
  4013ce:	48 83 c0 01          	add    $0x1,%rax
  4013d2:	48 83 f8 05          	cmp    $0x5,%rax
  4013d6:	76 e5                	jbe    4013bd <phase_5+0x1f>
  4013d8:	c6 44 24 06 00       	movb   $0x0,0x6(%rsp)
  4013dd:	be 00 44 60 00       	mov    $0x604400,%esi
  4013e2:	48 89 e7             	mov    %rsp,%rdi
  4013e5:	e8 90 04 00 00       	callq  40187a <strings_not_equal>
  4013ea:	84 c0                	test   %al,%al
  4013ec:	74 05                	je     4013f3 <phase_5+0x55>
  4013ee:	e8 9c 06 00 00       	callq  401a8f <explode_bomb>
  4013f3:	48 83 c4 10          	add    $0x10,%rsp
  4013f7:	5b                   	pop    %rbx
  4013f8:	c3                   	retq   

00000000004013f9 <phase_6>:
  4013f9:	41 54                	push   %r12
  4013fb:	55                   	push   %rbp
  4013fc:	53                   	push   %rbx
  4013fd:	48 83 ec 60          	sub    $0x60,%rsp
  401401:	48 8d 74 24 30       	lea    0x30(%rsp),%rsi
  401406:	e8 ba 06 00 00       	callq  401ac5 <read_six_numbers>
  40140b:	bd 00 00 00 00       	mov    $0x0,%ebp
  401410:	eb 3b                	jmp    40144d <phase_6+0x54>
  401412:	48 8b 44 ec 30       	mov    0x30(%rsp,%rbp,8),%rax
  401417:	48 83 e8 01          	sub    $0x1,%rax
  40141b:	48 83 f8 05          	cmp    $0x5,%rax
  40141f:	76 05                	jbe    401426 <phase_6+0x2d>
  401421:	e8 69 06 00 00       	callq  401a8f <explode_bomb>
  401426:	4c 8d 65 01          	lea    0x1(%rbp),%r12
  40142a:	4c 89 e3             	mov    %r12,%rbx
  40142d:	eb 15                	jmp    401444 <phase_6+0x4b>
  40142f:	48 8b 44 dc 30       	mov    0x30(%rsp,%rbx,8),%rax
  401434:	48 39 44 ec 30       	cmp    %rax,0x30(%rsp,%rbp,8)
  401439:	75 05                	jne    401440 <phase_6+0x47>
  40143b:	e8 4f 06 00 00       	callq  401a8f <explode_bomb>
  401440:	48 83 c3 01          	add    $0x1,%rbx
  401444:	48 83 fb 05          	cmp    $0x5,%rbx
  401448:	7e e5                	jle    40142f <phase_6+0x36>
  40144a:	4c 89 e5             	mov    %r12,%rbp
  40144d:	48 83 fd 05          	cmp    $0x5,%rbp
  401451:	7e bf                	jle    401412 <phase_6+0x19>
  401453:	b8 00 00 00 00       	mov    $0x0,%eax
  401458:	b9 07 00 00 00       	mov    $0x7,%ecx
  40145d:	eb 11                	jmp    401470 <phase_6+0x77>
  40145f:	48 89 ca             	mov    %rcx,%rdx
  401462:	48 2b 54 c4 30       	sub    0x30(%rsp,%rax,8),%rdx
  401467:	48 89 54 c4 30       	mov    %rdx,0x30(%rsp,%rax,8)
  40146c:	48 83 c0 01          	add    $0x1,%rax
  401470:	48 83 f8 05          	cmp    $0x5,%rax
  401474:	7e e9                	jle    40145f <phase_6+0x66>
  401476:	b9 00 00 00 00       	mov    $0x0,%ecx
  40147b:	eb 23                	jmp    4014a0 <phase_6+0xa7>
  40147d:	48 8b 52 10          	mov    0x10(%rdx),%rdx
  401481:	48 83 c0 01          	add    $0x1,%rax
  401485:	eb 0a                	jmp    401491 <phase_6+0x98>
  401487:	b8 01 00 00 00       	mov    $0x1,%eax
  40148c:	ba 40 43 60 00       	mov    $0x604340,%edx
  401491:	48 39 44 cc 30       	cmp    %rax,0x30(%rsp,%rcx,8)
  401496:	7f e5                	jg     40147d <phase_6+0x84>
  401498:	48 89 14 cc          	mov    %rdx,(%rsp,%rcx,8)
  40149c:	48 83 c1 01          	add    $0x1,%rcx
  4014a0:	48 83 f9 05          	cmp    $0x5,%rcx
  4014a4:	7e e1                	jle    401487 <phase_6+0x8e>
  4014a6:	48 8b 1c 24          	mov    (%rsp),%rbx
  4014aa:	48 89 d9             	mov    %rbx,%rcx
  4014ad:	b8 01 00 00 00       	mov    $0x1,%eax
  4014b2:	eb 0f                	jmp    4014c3 <phase_6+0xca>
  4014b4:	48 8b 14 c4          	mov    (%rsp,%rax,8),%rdx
  4014b8:	48 89 51 10          	mov    %rdx,0x10(%rcx)
  4014bc:	48 83 c0 01          	add    $0x1,%rax
  4014c0:	48 89 d1             	mov    %rdx,%rcx
  4014c3:	48 83 f8 05          	cmp    $0x5,%rax
  4014c7:	7e eb                	jle    4014b4 <phase_6+0xbb>
  4014c9:	48 c7 41 10 00 00 00 	movq   $0x0,0x10(%rcx)
  4014d0:	00 
  4014d1:	bd 00 00 00 00       	mov    $0x0,%ebp
  4014d6:	eb 19                	jmp    4014f1 <phase_6+0xf8>
  4014d8:	48 8b 43 10          	mov    0x10(%rbx),%rax
  4014dc:	48 8b 00             	mov    (%rax),%rax
  4014df:	48 39 03             	cmp    %rax,(%rbx)
  4014e2:	7d 05                	jge    4014e9 <phase_6+0xf0>
  4014e4:	e8 a6 05 00 00       	callq  401a8f <explode_bomb>
  4014e9:	48 8b 5b 10          	mov    0x10(%rbx),%rbx
  4014ed:	48 83 c5 01          	add    $0x1,%rbp
  4014f1:	48 83 fd 04          	cmp    $0x4,%rbp
  4014f5:	7e e1                	jle    4014d8 <phase_6+0xdf>
  4014f7:	48 83 c4 60          	add    $0x60,%rsp
  4014fb:	5b                   	pop    %rbx
  4014fc:	5d                   	pop    %rbp
  4014fd:	41 5c                	pop    %r12
  4014ff:	c3                   	retq   

0000000000401500 <fun7>:
  401500:	48 83 ec 08          	sub    $0x8,%rsp
  401504:	48 85 ff             	test   %rdi,%rdi
  401507:	74 38                	je     401541 <fun7+0x41>
  401509:	48 8b 02             	mov    (%rdx),%rax
  40150c:	48 c1 e0 08          	shl    $0x8,%rax
  401510:	48 03 07             	add    (%rdi),%rax
  401513:	48 89 02             	mov    %rax,(%rdx)
  401516:	48 8b 07             	mov    (%rdi),%rax
  401519:	48 39 f0             	cmp    %rsi,%rax
  40151c:	7e 0e                	jle    40152c <fun7+0x2c>
  40151e:	48 8b 7f 08          	mov    0x8(%rdi),%rdi
  401522:	e8 d9 ff ff ff       	callq  401500 <fun7>
  401527:	48 01 c0             	add    %rax,%rax
  40152a:	eb 23                	jmp    40154f <fun7+0x4f>
  40152c:	48 39 f0             	cmp    %rsi,%rax
  40152f:	74 19                	je     40154a <fun7+0x4a>
  401531:	48 8b 7f 10          	mov    0x10(%rdi),%rdi
  401535:	e8 c6 ff ff ff       	callq  401500 <fun7>
  40153a:	48 8d 44 00 01       	lea    0x1(%rax,%rax,1),%rax
  40153f:	eb 0e                	jmp    40154f <fun7+0x4f>
  401541:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  401548:	eb 05                	jmp    40154f <fun7+0x4f>
  40154a:	b8 00 00 00 00       	mov    $0x0,%eax
  40154f:	48 83 c4 08          	add    $0x8,%rsp
  401553:	c3                   	retq   

0000000000401554 <secret_phase>:
  401554:	48 83 ec 28          	sub    $0x28,%rsp
  401558:	e8 aa 05 00 00       	callq  401b07 <read_line>
  40155d:	48 c7 44 24 08 00 00 	movq   $0x0,0x8(%rsp)
  401564:	00 00 
  401566:	48 8d 4c 24 10       	lea    0x10(%rsp),%rcx
  40156b:	48 8d 54 24 18       	lea    0x18(%rsp),%rdx
  401570:	be 27 2c 40 00       	mov    $0x402c27,%esi
  401575:	48 89 c7             	mov    %rax,%rdi
  401578:	b8 00 00 00 00       	mov    $0x0,%eax
  40157d:	e8 be f7 ff ff       	callq  400d40 <__isoc99_sscanf@plt>
  401582:	83 f8 02             	cmp    $0x2,%eax
  401585:	74 05                	je     40158c <secret_phase+0x38>
  401587:	e8 03 05 00 00       	callq  401a8f <explode_bomb>
  40158c:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  401591:	48 83 e8 39          	sub    $0x39,%rax
  401595:	48 83 f8 7a          	cmp    $0x7a,%rax
  401599:	76 05                	jbe    4015a0 <secret_phase+0x4c>
  40159b:	e8 ef 04 00 00       	callq  401a8f <explode_bomb>
  4015a0:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
  4015a5:	48 8b 74 24 18       	mov    0x18(%rsp),%rsi
  4015aa:	bf 60 41 60 00       	mov    $0x604160,%edi
  4015af:	e8 4c ff ff ff       	callq  401500 <fun7>
  4015b4:	48 83 f8 01          	cmp    $0x1,%rax
  4015b8:	74 05                	je     4015bf <secret_phase+0x6b>
  4015ba:	e8 d0 04 00 00       	callq  401a8f <explode_bomb>
  4015bf:	48 8b 44 24 10       	mov    0x10(%rsp),%rax
  4015c4:	48 39 44 24 08       	cmp    %rax,0x8(%rsp)
  4015c9:	74 05                	je     4015d0 <secret_phase+0x7c>
  4015cb:	e8 bf 04 00 00       	callq  401a8f <explode_bomb>
  4015d0:	bf 80 2c 40 00       	mov    $0x402c80,%edi
  4015d5:	e8 56 f7 ff ff       	callq  400d30 <puts@plt>
  4015da:	e8 71 06 00 00       	callq  401c50 <phase_defused>
  4015df:	48 83 c4 28          	add    $0x28,%rsp
  4015e3:	c3                   	retq   
  4015e4:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4015eb:	00 00 00 
  4015ee:	66 90                	xchg   %ax,%ax

00000000004015f0 <safe_print>:
  4015f0:	48 83 ec 08          	sub    $0x8,%rsp
  4015f4:	48 89 fe             	mov    %rdi,%rsi
  4015f7:	b8 00 00 00 00       	mov    $0x0,%eax
  4015fc:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  401603:	f2 ae                	repnz scas %es:(%rdi),%al
  401605:	48 f7 d1             	not    %rcx
  401608:	48 8d 51 ff          	lea    -0x1(%rcx),%rdx
  40160c:	48 63 d2             	movslq %edx,%rdx
  40160f:	bf 01 00 00 00       	mov    $0x1,%edi
  401614:	e8 a7 f8 ff ff       	callq  400ec0 <write@plt>
  401619:	89 05 61 42 20 00    	mov    %eax,0x204261(%rip)        # 605880 <returncode>
  40161f:	48 83 c4 08          	add    $0x8,%rsp
  401623:	c3                   	retq   

0000000000401624 <sig_handler>:
  401624:	48 83 ec 08          	sub    $0x8,%rsp
  401628:	bf a8 2c 40 00       	mov    $0x402ca8,%edi
  40162d:	e8 be ff ff ff       	callq  4015f0 <safe_print>
  401632:	bf 03 00 00 00       	mov    $0x3,%edi
  401637:	e8 c4 f7 ff ff       	callq  400e00 <sleep@plt>
  40163c:	bf 07 30 40 00       	mov    $0x403007,%edi
  401641:	e8 aa ff ff ff       	callq  4015f0 <safe_print>
  401646:	48 8b 3d 23 42 20 00 	mov    0x204223(%rip),%rdi        # 605870 <stdout@@GLIBC_2.2.5>
  40164d:	e8 ae f8 ff ff       	callq  400f00 <fflush@plt>
  401652:	bf 01 00 00 00       	mov    $0x1,%edi
  401657:	e8 a4 f7 ff ff       	callq  400e00 <sleep@plt>
  40165c:	bf 0f 30 40 00       	mov    $0x40300f,%edi
  401661:	e8 8a ff ff ff       	callq  4015f0 <safe_print>
  401666:	bf 10 00 00 00       	mov    $0x10,%edi
  40166b:	e8 e0 f6 ff ff       	callq  400d50 <exit@plt>

0000000000401670 <delay_bomb>:
  401670:	48 81 ec a8 20 00 00 	sub    $0x20a8,%rsp
  401677:	bf 18 30 40 00       	mov    $0x403018,%edi
  40167c:	e8 df f7 ff ff       	callq  400e60 <getenv@plt>
  401681:	48 85 c0             	test   %rax,%rax
  401684:	75 20                	jne    4016a6 <delay_bomb+0x36>
  401686:	48 8b 0d db 41 20 00 	mov    0x2041db(%rip),%rcx        # 605868 <stderr@@GLIBC_2.2.5>
  40168d:	ba 1a 00 00 00       	mov    $0x1a,%edx
  401692:	be 01 00 00 00       	mov    $0x1,%esi
  401697:	bf 1d 30 40 00       	mov    $0x40301d,%edi
  40169c:	e8 ff f7 ff ff       	callq  400ea0 <fwrite@plt>
  4016a1:	e9 8c 01 00 00       	jmpq   401832 <delay_bomb+0x1c2>
  4016a6:	48 89 c1             	mov    %rax,%rcx
  4016a9:	ba 38 30 40 00       	mov    $0x403038,%edx
  4016ae:	be 00 10 00 00       	mov    $0x1000,%esi
  4016b3:	48 89 e7             	mov    %rsp,%rdi
  4016b6:	b8 00 00 00 00       	mov    $0x0,%eax
  4016bb:	e8 30 f6 ff ff       	callq  400cf0 <snprintf@plt>
  4016c0:	3d ff 0f 00 00       	cmp    $0xfff,%eax
  4016c5:	76 20                	jbe    4016e7 <delay_bomb+0x77>
  4016c7:	48 8b 0d 9a 41 20 00 	mov    0x20419a(%rip),%rcx        # 605868 <stderr@@GLIBC_2.2.5>
  4016ce:	ba 1b 00 00 00       	mov    $0x1b,%edx
  4016d3:	be 01 00 00 00       	mov    $0x1,%esi
  4016d8:	bf 42 30 40 00       	mov    $0x403042,%edi
  4016dd:	e8 be f7 ff ff       	callq  400ea0 <fwrite@plt>
  4016e2:	e9 4b 01 00 00       	jmpq   401832 <delay_bomb+0x1c2>
  4016e7:	be ff 01 00 00       	mov    $0x1ff,%esi
  4016ec:	48 89 e7             	mov    %rsp,%rdi
  4016ef:	e8 fc f7 ff ff       	callq  400ef0 <mkdir@plt>
  4016f4:	85 c0                	test   %eax,%eax
  4016f6:	79 19                	jns    401711 <delay_bomb+0xa1>
  4016f8:	e8 83 f7 ff ff       	callq  400e80 <__errno_location@plt>
  4016fd:	83 38 11             	cmpl   $0x11,(%rax)
  401700:	74 0f                	je     401711 <delay_bomb+0xa1>
  401702:	bf 5e 30 40 00       	mov    $0x40305e,%edi
  401707:	e8 a4 f7 ff ff       	callq  400eb0 <perror@plt>
  40170c:	e9 21 01 00 00       	jmpq   401832 <delay_bomb+0x1c2>
  401711:	48 89 e6             	mov    %rsp,%rsi
  401714:	48 8d bc 24 00 10 00 	lea    0x1000(%rsp),%rdi
  40171b:	00 
  40171c:	e8 6f f7 ff ff       	callq  400e90 <strcpy@plt>
  401721:	48 8d 8c 24 00 10 00 	lea    0x1000(%rsp),%rcx
  401728:	00 
  401729:	ba 64 30 40 00       	mov    $0x403064,%edx
  40172e:	be 00 10 00 00       	mov    $0x1000,%esi
  401733:	48 89 e7             	mov    %rsp,%rdi
  401736:	b8 00 00 00 00       	mov    $0x0,%eax
  40173b:	e8 b0 f5 ff ff       	callq  400cf0 <snprintf@plt>
  401740:	3d ff 0f 00 00       	cmp    $0xfff,%eax
  401745:	76 20                	jbe    401767 <delay_bomb+0xf7>
  401747:	48 8b 0d 1a 41 20 00 	mov    0x20411a(%rip),%rcx        # 605868 <stderr@@GLIBC_2.2.5>
  40174e:	ba 1b 00 00 00       	mov    $0x1b,%edx
  401753:	be 01 00 00 00       	mov    $0x1,%esi
  401758:	bf 42 30 40 00       	mov    $0x403042,%edi
  40175d:	e8 3e f7 ff ff       	callq  400ea0 <fwrite@plt>
  401762:	e9 cb 00 00 00       	jmpq   401832 <delay_bomb+0x1c2>
  401767:	48 8d 94 24 10 20 00 	lea    0x2010(%rsp),%rdx
  40176e:	00 
  40176f:	48 89 e6             	mov    %rsp,%rsi
  401772:	bf 01 00 00 00       	mov    $0x1,%edi
  401777:	e8 54 f6 ff ff       	callq  400dd0 <__xstat@plt>
  40177c:	85 c0                	test   %eax,%eax
  40177e:	79 3d                	jns    4017bd <delay_bomb+0x14d>
  401780:	e8 fb f6 ff ff       	callq  400e80 <__errno_location@plt>
  401785:	83 38 02             	cmpl   $0x2,(%rax)
  401788:	74 0f                	je     401799 <delay_bomb+0x129>
  40178a:	bf 79 30 40 00       	mov    $0x403079,%edi
  40178f:	e8 1c f7 ff ff       	callq  400eb0 <perror@plt>
  401794:	e9 99 00 00 00       	jmpq   401832 <delay_bomb+0x1c2>
  401799:	be b6 01 00 00       	mov    $0x1b6,%esi
  40179e:	48 89 e7             	mov    %rsp,%rdi
  4017a1:	e8 0a f6 ff ff       	callq  400db0 <creat@plt>
  4017a6:	85 c0                	test   %eax,%eax
  4017a8:	79 0c                	jns    4017b6 <delay_bomb+0x146>
  4017aa:	bf 7e 30 40 00       	mov    $0x40307e,%edi
  4017af:	e8 fc f6 ff ff       	callq  400eb0 <perror@plt>
  4017b4:	eb 7c                	jmp    401832 <delay_bomb+0x1c2>
  4017b6:	89 c7                	mov    %eax,%edi
  4017b8:	e8 43 f5 ff ff       	callq  400d00 <close@plt>
  4017bd:	48 8b 84 24 58 20 00 	mov    0x2058(%rsp),%rax
  4017c4:	00 
  4017c5:	48 8b 94 24 60 20 00 	mov    0x2060(%rsp),%rdx
  4017cc:	00 
  4017cd:	48 89 84 24 00 20 00 	mov    %rax,0x2000(%rsp)
  4017d4:	00 
  4017d5:	48 89 94 24 08 20 00 	mov    %rdx,0x2008(%rsp)
  4017dc:	00 
  4017dd:	48 83 84 24 00 20 00 	addq   $0x5,0x2000(%rsp)
  4017e4:	00 05 
  4017e6:	b9 00 00 00 00       	mov    $0x0,%ecx
  4017eb:	48 8d 94 24 00 20 00 	lea    0x2000(%rsp),%rdx
  4017f2:	00 
  4017f3:	be 01 00 00 00       	mov    $0x1,%esi
  4017f8:	bf 00 00 00 00       	mov    $0x0,%edi
  4017fd:	e8 2e f6 ff ff       	callq  400e30 <clock_nanosleep@plt>
  401802:	be 01 02 00 00       	mov    $0x201,%esi
  401807:	48 89 e7             	mov    %rsp,%rdi
  40180a:	b8 00 00 00 00       	mov    $0x0,%eax
  40180f:	e8 cc f6 ff ff       	callq  400ee0 <open@plt>
  401814:	85 c0                	test   %eax,%eax
  401816:	79 0c                	jns    401824 <delay_bomb+0x1b4>
  401818:	bf 84 30 40 00       	mov    $0x403084,%edi
  40181d:	e8 8e f6 ff ff       	callq  400eb0 <perror@plt>
  401822:	eb 18                	jmp    40183c <delay_bomb+0x1cc>
  401824:	89 c7                	mov    %eax,%edi
  401826:	e8 d5 f4 ff ff       	callq  400d00 <close@plt>
  40182b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  401830:	eb 0a                	jmp    40183c <delay_bomb+0x1cc>
  401832:	bf 05 00 00 00       	mov    $0x5,%edi
  401837:	e8 c4 f5 ff ff       	callq  400e00 <sleep@plt>
  40183c:	48 81 c4 a8 20 00 00 	add    $0x20a8,%rsp
  401843:	c3                   	retq   

0000000000401844 <invalid_phase>:
  401844:	48 83 ec 08          	sub    $0x8,%rsp
  401848:	48 89 fe             	mov    %rdi,%rsi
  40184b:	bf 89 30 40 00       	mov    $0x403089,%edi
  401850:	b8 00 00 00 00       	mov    $0x0,%eax
  401855:	e8 86 f4 ff ff       	callq  400ce0 <printf@plt>
  40185a:	bf 08 00 00 00       	mov    $0x8,%edi
  40185f:	e8 ec f4 ff ff       	callq  400d50 <exit@plt>

0000000000401864 <string_length>:
  401864:	b8 00 00 00 00       	mov    $0x0,%eax
  401869:	eb 08                	jmp    401873 <string_length+0xf>
  40186b:	48 83 c7 01          	add    $0x1,%rdi
  40186f:	48 83 c0 01          	add    $0x1,%rax
  401873:	80 3f 00             	cmpb   $0x0,(%rdi)
  401876:	75 f3                	jne    40186b <string_length+0x7>
  401878:	f3 c3                	repz retq 

000000000040187a <strings_not_equal>:
  40187a:	41 54                	push   %r12
  40187c:	55                   	push   %rbp
  40187d:	53                   	push   %rbx
  40187e:	48 89 fb             	mov    %rdi,%rbx
  401881:	48 89 f5             	mov    %rsi,%rbp
  401884:	e8 db ff ff ff       	callq  401864 <string_length>
  401889:	49 89 c4             	mov    %rax,%r12
  40188c:	48 89 ef             	mov    %rbp,%rdi
  40188f:	e8 d0 ff ff ff       	callq  401864 <string_length>
  401894:	49 39 c4             	cmp    %rax,%r12
  401897:	75 1a                	jne    4018b3 <strings_not_equal+0x39>
  401899:	eb 0f                	jmp    4018aa <strings_not_equal+0x30>
  40189b:	3a 45 00             	cmp    0x0(%rbp),%al
  40189e:	66 90                	xchg   %ax,%ax
  4018a0:	75 18                	jne    4018ba <strings_not_equal+0x40>
  4018a2:	48 83 c3 01          	add    $0x1,%rbx
  4018a6:	48 83 c5 01          	add    $0x1,%rbp
  4018aa:	0f b6 03             	movzbl (%rbx),%eax
  4018ad:	84 c0                	test   %al,%al
  4018af:	75 ea                	jne    40189b <strings_not_equal+0x21>
  4018b1:	eb 0c                	jmp    4018bf <strings_not_equal+0x45>
  4018b3:	b8 01 00 00 00       	mov    $0x1,%eax
  4018b8:	eb 05                	jmp    4018bf <strings_not_equal+0x45>
  4018ba:	b8 01 00 00 00       	mov    $0x1,%eax
  4018bf:	5b                   	pop    %rbx
  4018c0:	5d                   	pop    %rbp
  4018c1:	41 5c                	pop    %r12
  4018c3:	c3                   	retq   

00000000004018c4 <fs>:
  4018c4:	ba 00 00 00 00       	mov    $0x0,%edx
  4018c9:	eb 2d                	jmp    4018f8 <fs+0x34>
  4018cb:	83 e8 61             	sub    $0x61,%eax
  4018ce:	3c 14                	cmp    $0x14,%al
  4018d0:	77 23                	ja     4018f5 <fs+0x31>
  4018d2:	0f b6 c0             	movzbl %al,%eax
  4018d5:	ff 24 c5 c0 32 40 00 	jmpq   *0x4032c0(,%rax,8)
  4018dc:	c6 01 6f             	movb   $0x6f,(%rcx)
  4018df:	eb 14                	jmp    4018f5 <fs+0x31>
  4018e1:	c6 01 69             	movb   $0x69,(%rcx)
  4018e4:	eb 0f                	jmp    4018f5 <fs+0x31>
  4018e6:	c6 01 65             	movb   $0x65,(%rcx)
  4018e9:	eb 0a                	jmp    4018f5 <fs+0x31>
  4018eb:	c6 01 61             	movb   $0x61,(%rcx)
  4018ee:	66 90                	xchg   %ax,%ax
  4018f0:	eb 03                	jmp    4018f5 <fs+0x31>
  4018f2:	c6 01 75             	movb   $0x75,(%rcx)
  4018f5:	83 c2 01             	add    $0x1,%edx
  4018f8:	48 63 ca             	movslq %edx,%rcx
  4018fb:	48 01 f9             	add    %rdi,%rcx
  4018fe:	0f b6 01             	movzbl (%rcx),%eax
  401901:	84 c0                	test   %al,%al
  401903:	75 c6                	jne    4018cb <fs+0x7>
  401905:	f3 c3                	repz retq 

0000000000401907 <initialize_bomb_solve>:
  401907:	f3 c3                	repz retq 

0000000000401909 <blank_line>:
  401909:	55                   	push   %rbp
  40190a:	53                   	push   %rbx
  40190b:	48 83 ec 08          	sub    $0x8,%rsp
  40190f:	48 89 fb             	mov    %rdi,%rbx
  401912:	eb 17                	jmp    40192b <blank_line+0x22>
  401914:	e8 c7 f4 ff ff       	callq  400de0 <__ctype_b_loc@plt>
  401919:	48 8b 00             	mov    (%rax),%rax
  40191c:	48 83 c3 01          	add    $0x1,%rbx
  401920:	48 0f be ed          	movsbq %bpl,%rbp
  401924:	f6 44 68 01 20       	testb  $0x20,0x1(%rax,%rbp,2)
  401929:	74 0f                	je     40193a <blank_line+0x31>
  40192b:	0f b6 2b             	movzbl (%rbx),%ebp
  40192e:	40 84 ed             	test   %bpl,%bpl
  401931:	75 e1                	jne    401914 <blank_line+0xb>
  401933:	b8 01 00 00 00       	mov    $0x1,%eax
  401938:	eb 05                	jmp    40193f <blank_line+0x36>
  40193a:	b8 00 00 00 00       	mov    $0x0,%eax
  40193f:	48 83 c4 08          	add    $0x8,%rsp
  401943:	5b                   	pop    %rbx
  401944:	5d                   	pop    %rbp
  401945:	c3                   	retq   

0000000000401946 <skip>:
  401946:	53                   	push   %rbx
  401947:	48 8b 05 3a 3f 20 00 	mov    0x203f3a(%rip),%rax        # 605888 <num_input_strings>
  40194e:	48 8d 3c 80          	lea    (%rax,%rax,4),%rdi
  401952:	48 c1 e7 04          	shl    $0x4,%rdi
  401956:	48 81 c7 a0 58 60 00 	add    $0x6058a0,%rdi
  40195d:	48 8b 15 2c 3f 20 00 	mov    0x203f2c(%rip),%rdx        # 605890 <infile>
  401964:	be 50 00 00 00       	mov    $0x50,%esi
  401969:	e8 32 f4 ff ff       	callq  400da0 <fgets@plt>
  40196e:	48 89 c3             	mov    %rax,%rbx
  401971:	48 85 c0             	test   %rax,%rax
  401974:	74 0c                	je     401982 <skip+0x3c>
  401976:	48 89 c7             	mov    %rax,%rdi
  401979:	e8 8b ff ff ff       	callq  401909 <blank_line>
  40197e:	85 c0                	test   %eax,%eax
  401980:	75 c5                	jne    401947 <skip+0x1>
  401982:	48 89 d8             	mov    %rbx,%rax
  401985:	5b                   	pop    %rbx
  401986:	c3                   	retq   

0000000000401987 <send_msg>:
  401987:	53                   	push   %rbx
  401988:	48 81 ec 10 40 00 00 	sub    $0x4010,%rsp
  40198f:	89 fb                	mov    %edi,%ebx
  401991:	83 ff 01             	cmp    $0x1,%edi
  401994:	74 24                	je     4019ba <send_msg+0x33>
  401996:	83 ff 01             	cmp    $0x1,%edi
  401999:	72 07                	jb     4019a2 <send_msg+0x1b>
  40199b:	83 ff 02             	cmp    $0x2,%edi
  40199e:	74 0a                	je     4019aa <send_msg+0x23>
  4019a0:	eb 10                	jmp    4019b2 <send_msg+0x2b>
  4019a2:	41 b8 9a 30 40 00    	mov    $0x40309a,%r8d
  4019a8:	eb 16                	jmp    4019c0 <send_msg+0x39>
  4019aa:	41 b8 ab 30 40 00    	mov    $0x4030ab,%r8d
  4019b0:	eb 0e                	jmp    4019c0 <send_msg+0x39>
  4019b2:	41 b8 b0 30 40 00    	mov    $0x4030b0,%r8d
  4019b8:	eb 06                	jmp    4019c0 <send_msg+0x39>
  4019ba:	41 b8 a3 30 40 00    	mov    $0x4030a3,%r8d
  4019c0:	4c 8b 0d c1 3e 20 00 	mov    0x203ec1(%rip),%r9        # 605888 <num_input_strings>
  4019c7:	4b 8d 54 89 fb       	lea    -0x5(%r9,%r9,4),%rdx
  4019cc:	48 89 d0             	mov    %rdx,%rax
  4019cf:	48 c1 e0 04          	shl    $0x4,%rax
  4019d3:	48 8d 90 a0 58 60 00 	lea    0x6058a0(%rax),%rdx
  4019da:	48 89 d7             	mov    %rdx,%rdi
  4019dd:	b8 00 00 00 00       	mov    $0x0,%eax
  4019e2:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  4019e9:	f2 ae                	repnz scas %es:(%rdi),%al
  4019eb:	48 f7 d1             	not    %rcx
  4019ee:	48 83 c1 63          	add    $0x63,%rcx
  4019f2:	48 81 f9 00 20 00 00 	cmp    $0x2000,%rcx
  4019f9:	76 1d                	jbe    401a18 <send_msg+0x91>
  4019fb:	83 fb 02             	cmp    $0x2,%ebx
  4019fe:	0f 84 82 00 00 00    	je     401a86 <send_msg+0xff>
  401a04:	bf e8 2c 40 00       	mov    $0x402ce8,%edi
  401a09:	e8 d2 f2 ff ff       	callq  400ce0 <printf@plt>
  401a0e:	bf 08 00 00 00       	mov    $0x8,%edi
  401a13:	e8 38 f3 ff ff       	callq  400d50 <exit@plt>
  401a18:	48 89 14 24          	mov    %rdx,(%rsp)
  401a1c:	b9 40 4d 60 00       	mov    $0x604d40,%ecx
  401a21:	8b 15 19 3b 20 00    	mov    0x203b19(%rip),%edx        # 605540 <bomb_id>
  401a27:	be b8 30 40 00       	mov    $0x4030b8,%esi
  401a2c:	48 8d bc 24 10 20 00 	lea    0x2010(%rsp),%rdi
  401a33:	00 
  401a34:	b8 00 00 00 00       	mov    $0x0,%eax
  401a39:	e8 b2 f3 ff ff       	callq  400df0 <sprintf@plt>
  401a3e:	4c 8d 4c 24 10       	lea    0x10(%rsp),%r9
  401a43:	41 b8 00 00 00 00    	mov    $0x0,%r8d
  401a49:	48 8d 8c 24 10 20 00 	lea    0x2010(%rsp),%rcx
  401a50:	00 
  401a51:	ba 40 45 60 00       	mov    $0x604540,%edx
  401a56:	be 40 49 60 00       	mov    $0x604940,%esi
  401a5b:	bf 40 51 60 00       	mov    $0x605140,%edi
  401a60:	e8 64 0f 00 00       	callq  4029c9 <driver_post>
  401a65:	c1 e8 1f             	shr    $0x1f,%eax
  401a68:	83 fb 02             	cmp    $0x2,%ebx
  401a6b:	0f 95 c2             	setne  %dl
  401a6e:	84 c2                	test   %al,%dl
  401a70:	74 14                	je     401a86 <send_msg+0xff>
  401a72:	48 8d 7c 24 10       	lea    0x10(%rsp),%rdi
  401a77:	e8 b4 f2 ff ff       	callq  400d30 <puts@plt>
  401a7c:	bf 00 00 00 00       	mov    $0x0,%edi
  401a81:	e8 ca f2 ff ff       	callq  400d50 <exit@plt>
  401a86:	48 81 c4 10 40 00 00 	add    $0x4010,%rsp
  401a8d:	5b                   	pop    %rbx
  401a8e:	c3                   	retq   

0000000000401a8f <explode_bomb>:
  401a8f:	48 83 ec 08          	sub    $0x8,%rsp
  401a93:	bf c8 30 40 00       	mov    $0x4030c8,%edi
  401a98:	e8 93 f2 ff ff       	callq  400d30 <puts@plt>
  401a9d:	bf d1 30 40 00       	mov    $0x4030d1,%edi
  401aa2:	e8 89 f2 ff ff       	callq  400d30 <puts@plt>
  401aa7:	bf 00 00 00 00       	mov    $0x0,%edi
  401aac:	e8 d6 fe ff ff       	callq  401987 <send_msg>
  401ab1:	bf 10 2d 40 00       	mov    $0x402d10,%edi
  401ab6:	e8 75 f2 ff ff       	callq  400d30 <puts@plt>
  401abb:	bf 08 00 00 00       	mov    $0x8,%edi
  401ac0:	e8 8b f2 ff ff       	callq  400d50 <exit@plt>

0000000000401ac5 <read_six_numbers>:
  401ac5:	48 83 ec 18          	sub    $0x18,%rsp
  401ac9:	48 89 f2             	mov    %rsi,%rdx
  401acc:	48 8d 76 28          	lea    0x28(%rsi),%rsi
  401ad0:	48 8d 42 20          	lea    0x20(%rdx),%rax
  401ad4:	48 8d 4a 08          	lea    0x8(%rdx),%rcx
  401ad8:	48 89 74 24 08       	mov    %rsi,0x8(%rsp)
  401add:	48 89 04 24          	mov    %rax,(%rsp)
  401ae1:	4c 8d 4a 18          	lea    0x18(%rdx),%r9
  401ae5:	4c 8d 42 10          	lea    0x10(%rdx),%r8
  401ae9:	be e8 30 40 00       	mov    $0x4030e8,%esi
  401aee:	b8 00 00 00 00       	mov    $0x0,%eax
  401af3:	e8 48 f2 ff ff       	callq  400d40 <__isoc99_sscanf@plt>
  401af8:	83 f8 05             	cmp    $0x5,%eax
  401afb:	7f 05                	jg     401b02 <read_six_numbers+0x3d>
  401afd:	e8 8d ff ff ff       	callq  401a8f <explode_bomb>
  401b02:	48 83 c4 18          	add    $0x18,%rsp
  401b06:	c3                   	retq   

0000000000401b07 <read_line>:
  401b07:	53                   	push   %rbx
  401b08:	e8 39 fe ff ff       	callq  401946 <skip>
  401b0d:	48 85 c0             	test   %rax,%rax
  401b10:	75 69                	jne    401b7b <read_line+0x74>
  401b12:	48 8b 05 47 3d 20 00 	mov    0x203d47(%rip),%rax        # 605860 <stdin@@GLIBC_2.2.5>
  401b19:	48 39 05 70 3d 20 00 	cmp    %rax,0x203d70(%rip)        # 605890 <infile>
  401b20:	75 14                	jne    401b36 <read_line+0x2f>
  401b22:	bf 00 31 40 00       	mov    $0x403100,%edi
  401b27:	e8 04 f2 ff ff       	callq  400d30 <puts@plt>
  401b2c:	bf 00 00 00 00       	mov    $0x0,%edi
  401b31:	e8 1a f2 ff ff       	callq  400d50 <exit@plt>
  401b36:	bf 1e 31 40 00       	mov    $0x40311e,%edi
  401b3b:	e8 20 f3 ff ff       	callq  400e60 <getenv@plt>
  401b40:	48 85 c0             	test   %rax,%rax
  401b43:	74 0a                	je     401b4f <read_line+0x48>
  401b45:	bf 00 00 00 00       	mov    $0x0,%edi
  401b4a:	e8 01 f2 ff ff       	callq  400d50 <exit@plt>
  401b4f:	48 8b 05 0a 3d 20 00 	mov    0x203d0a(%rip),%rax        # 605860 <stdin@@GLIBC_2.2.5>
  401b56:	48 89 05 33 3d 20 00 	mov    %rax,0x203d33(%rip)        # 605890 <infile>
  401b5d:	e8 e4 fd ff ff       	callq  401946 <skip>
  401b62:	48 85 c0             	test   %rax,%rax
  401b65:	75 14                	jne    401b7b <read_line+0x74>
  401b67:	bf 00 31 40 00       	mov    $0x403100,%edi
  401b6c:	e8 bf f1 ff ff       	callq  400d30 <puts@plt>
  401b71:	bf 00 00 00 00       	mov    $0x0,%edi
  401b76:	e8 d5 f1 ff ff       	callq  400d50 <exit@plt>
  401b7b:	48 8b 15 06 3d 20 00 	mov    0x203d06(%rip),%rdx        # 605888 <num_input_strings>
  401b82:	48 8d 04 92          	lea    (%rdx,%rdx,4),%rax
  401b86:	48 c1 e0 04          	shl    $0x4,%rax
  401b8a:	48 8d 98 a0 58 60 00 	lea    0x6058a0(%rax),%rbx
  401b91:	48 89 df             	mov    %rbx,%rdi
  401b94:	b8 00 00 00 00       	mov    $0x0,%eax
  401b99:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  401ba0:	f2 ae                	repnz scas %es:(%rdi),%al
  401ba2:	48 f7 d1             	not    %rcx
  401ba5:	48 83 e9 01          	sub    $0x1,%rcx
  401ba9:	48 83 f9 4e          	cmp    $0x4e,%rcx
  401bad:	76 47                	jbe    401bf6 <read_line+0xef>
  401baf:	bf 29 31 40 00       	mov    $0x403129,%edi
  401bb4:	e8 77 f1 ff ff       	callq  400d30 <puts@plt>
  401bb9:	48 8b 05 c8 3c 20 00 	mov    0x203cc8(%rip),%rax        # 605888 <num_input_strings>
  401bc0:	48 8d 50 01          	lea    0x1(%rax),%rdx
  401bc4:	48 89 15 bd 3c 20 00 	mov    %rdx,0x203cbd(%rip)        # 605888 <num_input_strings>
  401bcb:	48 6b c0 50          	imul   $0x50,%rax,%rax
  401bcf:	48 bb 2a 2a 2a 74 72 	movabs $0x636e7572742a2a2a,%rbx
  401bd6:	75 6e 63 
  401bd9:	48 89 98 a0 58 60 00 	mov    %rbx,0x6058a0(%rax)
  401be0:	48 bb 61 74 65 64 2a 	movabs $0x2a2a2a64657461,%rbx
  401be7:	2a 2a 00 
  401bea:	48 89 98 a8 58 60 00 	mov    %rbx,0x6058a8(%rax)
  401bf1:	e8 99 fe ff ff       	callq  401a8f <explode_bomb>
  401bf6:	48 8d 34 92          	lea    (%rdx,%rdx,4),%rsi
  401bfa:	48 c1 e6 04          	shl    $0x4,%rsi
  401bfe:	80 bc 31 9f 58 60 00 	cmpb   $0xa,0x60589f(%rcx,%rsi,1)
  401c05:	0a 
  401c06:	75 10                	jne    401c18 <read_line+0x111>
  401c08:	48 8d 34 92          	lea    (%rdx,%rdx,4),%rsi
  401c0c:	48 c1 e6 04          	shl    $0x4,%rsi
  401c10:	c6 84 31 9f 58 60 00 	movb   $0x0,0x60589f(%rcx,%rsi,1)
  401c17:	00 
  401c18:	48 83 e9 02          	sub    $0x2,%rcx
  401c1c:	48 8d 34 92          	lea    (%rdx,%rdx,4),%rsi
  401c20:	48 c1 e6 04          	shl    $0x4,%rsi
  401c24:	80 bc 31 a0 58 60 00 	cmpb   $0xd,0x6058a0(%rcx,%rsi,1)
  401c2b:	0d 
  401c2c:	75 08                	jne    401c36 <read_line+0x12f>
  401c2e:	c6 84 31 a0 58 60 00 	movb   $0x0,0x6058a0(%rcx,%rsi,1)
  401c35:	00 
  401c36:	48 83 c2 01          	add    $0x1,%rdx
  401c3a:	48 89 15 47 3c 20 00 	mov    %rdx,0x203c47(%rip)        # 605888 <num_input_strings>
  401c41:	bf 02 00 00 00       	mov    $0x2,%edi
  401c46:	e8 3c fd ff ff       	callq  401987 <send_msg>
  401c4b:	48 89 d8             	mov    %rbx,%rax
  401c4e:	5b                   	pop    %rbx
  401c4f:	c3                   	retq   

0000000000401c50 <phase_defused>:
  401c50:	48 83 ec 78          	sub    $0x78,%rsp
  401c54:	bf 01 00 00 00       	mov    $0x1,%edi
  401c59:	e8 29 fd ff ff       	callq  401987 <send_msg>
  401c5e:	48 83 3d 22 3c 20 00 	cmpq   $0x6,0x203c22(%rip)        # 605888 <num_input_strings>
  401c65:	06 
  401c66:	0f 85 83 00 00 00    	jne    401cef <phase_defused+0x9f>
  401c6c:	4c 8d 4c 24 08       	lea    0x8(%rsp),%r9
  401c71:	4c 8d 44 24 20       	lea    0x20(%rsp),%r8
  401c76:	48 8d 4c 24 10       	lea    0x10(%rsp),%rcx
  401c7b:	48 8d 54 24 18       	lea    0x18(%rsp),%rdx
  401c80:	be 44 31 40 00       	mov    $0x403144,%esi
  401c85:	bf 90 59 60 00       	mov    $0x605990,%edi
  401c8a:	b8 00 00 00 00       	mov    $0x0,%eax
  401c8f:	e8 ac f0 ff ff       	callq  400d40 <__isoc99_sscanf@plt>
  401c94:	83 f8 04             	cmp    $0x4,%eax
  401c97:	75 42                	jne    401cdb <phase_defused+0x8b>
  401c99:	48 8d 7c 24 20       	lea    0x20(%rsp),%rdi
  401c9e:	e8 c1 fb ff ff       	callq  401864 <string_length>
  401ca3:	48 3b 44 24 08       	cmp    0x8(%rsp),%rax
  401ca8:	75 31                	jne    401cdb <phase_defused+0x8b>
  401caa:	be 80 44 60 00       	mov    $0x604480,%esi
  401caf:	48 8d 7c 24 20       	lea    0x20(%rsp),%rdi
  401cb4:	e8 c1 fb ff ff       	callq  40187a <strings_not_equal>
  401cb9:	84 c0                	test   %al,%al
  401cbb:	75 1e                	jne    401cdb <phase_defused+0x8b>
  401cbd:	bf 38 2d 40 00       	mov    $0x402d38,%edi
  401cc2:	e8 69 f0 ff ff       	callq  400d30 <puts@plt>
  401cc7:	bf 60 2d 40 00       	mov    $0x402d60,%edi
  401ccc:	e8 5f f0 ff ff       	callq  400d30 <puts@plt>
  401cd1:	b8 00 00 00 00       	mov    $0x0,%eax
  401cd6:	e8 79 f8 ff ff       	callq  401554 <secret_phase>
  401cdb:	bf 98 2d 40 00       	mov    $0x402d98,%edi
  401ce0:	e8 4b f0 ff ff       	callq  400d30 <puts@plt>
  401ce5:	bf c8 2d 40 00       	mov    $0x402dc8,%edi
  401cea:	e8 41 f0 ff ff       	callq  400d30 <puts@plt>
  401cef:	48 83 c4 78          	add    $0x78,%rsp
  401cf3:	c3                   	retq   

0000000000401cf4 <checkhash>:
  401cf4:	b8 01 00 00 00       	mov    $0x1,%eax
  401cf9:	c3                   	retq   

0000000000401cfa <initialize_bomb>:
  401cfa:	53                   	push   %rbx
  401cfb:	48 81 ec 40 20 00 00 	sub    $0x2040,%rsp
  401d02:	be 24 16 40 00       	mov    $0x401624,%esi
  401d07:	bf 02 00 00 00       	mov    $0x2,%edi
  401d0c:	e8 2f f1 ff ff       	callq  400e40 <signal@plt>
  401d11:	bf e0 44 60 00       	mov    $0x6044e0,%edi
  401d16:	e8 a9 fb ff ff       	callq  4018c4 <fs>
  401d1b:	bf 80 44 60 00       	mov    $0x604480,%edi
  401d20:	e8 9f fb ff ff       	callq  4018c4 <fs>
  401d25:	bf 00 44 60 00       	mov    $0x604400,%edi
  401d2a:	e8 95 fb ff ff       	callq  4018c4 <fs>
  401d2f:	e8 c0 ff ff ff       	callq  401cf4 <checkhash>
  401d34:	85 c0                	test   %eax,%eax
  401d36:	75 14                	jne    401d4c <initialize_bomb+0x52>
  401d38:	bf 10 2e 40 00       	mov    $0x402e10,%edi
  401d3d:	e8 ee ef ff ff       	callq  400d30 <puts@plt>
  401d42:	bf 08 00 00 00       	mov    $0x8,%edi
  401d47:	e8 04 f0 ff ff       	callq  400d50 <exit@plt>
  401d4c:	be 40 00 00 00       	mov    $0x40,%esi
  401d51:	48 8d bc 24 00 20 00 	lea    0x2000(%rsp),%rdi
  401d58:	00 
  401d59:	e8 c2 f0 ff ff       	callq  400e20 <gethostname@plt>
  401d5e:	85 c0                	test   %eax,%eax
  401d60:	74 2a                	je     401d8c <initialize_bomb+0x92>
  401d62:	bf c0 2e 40 00       	mov    $0x402ec0,%edi
  401d67:	e8 c4 ef ff ff       	callq  400d30 <puts@plt>
  401d6c:	bf 08 00 00 00       	mov    $0x8,%edi
  401d71:	e8 da ef ff ff       	callq  400d50 <exit@plt>
  401d76:	48 8d b4 24 00 20 00 	lea    0x2000(%rsp),%rsi
  401d7d:	00 
  401d7e:	e8 dd ef ff ff       	callq  400d60 <strcasecmp@plt>
  401d83:	85 c0                	test   %eax,%eax
  401d85:	74 21                	je     401da8 <initialize_bomb+0xae>
  401d87:	83 c3 01             	add    $0x1,%ebx
  401d8a:	eb 05                	jmp    401d91 <initialize_bomb+0x97>
  401d8c:	bb 00 00 00 00       	mov    $0x0,%ebx
  401d91:	48 63 c3             	movslq %ebx,%rax
  401d94:	48 8b 3c c5 a0 55 60 	mov    0x6055a0(,%rax,8),%rdi
  401d9b:	00 
  401d9c:	48 85 ff             	test   %rdi,%rdi
  401d9f:	75 d5                	jne    401d76 <initialize_bomb+0x7c>
  401da1:	b8 00 00 00 00       	mov    $0x0,%eax
  401da6:	eb 05                	jmp    401dad <initialize_bomb+0xb3>
  401da8:	b8 01 00 00 00       	mov    $0x1,%eax
  401dad:	85 c0                	test   %eax,%eax
  401daf:	75 14                	jne    401dc5 <initialize_bomb+0xcb>
  401db1:	bf f8 2e 40 00       	mov    $0x402ef8,%edi
  401db6:	e8 75 ef ff ff       	callq  400d30 <puts@plt>
  401dbb:	bf 08 00 00 00       	mov    $0x8,%edi
  401dc0:	e8 8b ef ff ff       	callq  400d50 <exit@plt>
  401dc5:	48 89 e7             	mov    %rsp,%rdi
  401dc8:	e8 33 0a 00 00       	callq  402800 <init_driver>
  401dcd:	85 c0                	test   %eax,%eax
  401dcf:	79 1c                	jns    401ded <initialize_bomb+0xf3>
  401dd1:	48 89 e6             	mov    %rsp,%rsi
  401dd4:	bf 53 31 40 00       	mov    $0x403153,%edi
  401dd9:	b8 00 00 00 00       	mov    $0x0,%eax
  401dde:	e8 fd ee ff ff       	callq  400ce0 <printf@plt>
  401de3:	bf 08 00 00 00       	mov    $0x8,%edi
  401de8:	e8 63 ef ff ff       	callq  400d50 <exit@plt>
  401ded:	e8 7e f8 ff ff       	callq  401670 <delay_bomb>
  401df2:	48 81 c4 40 20 00 00 	add    $0x2040,%rsp
  401df9:	5b                   	pop    %rbx
  401dfa:	c3                   	retq   
  401dfb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000401e00 <rio_readinitb>:
  401e00:	89 37                	mov    %esi,(%rdi)
  401e02:	c7 47 04 00 00 00 00 	movl   $0x0,0x4(%rdi)
  401e09:	48 8d 47 10          	lea    0x10(%rdi),%rax
  401e0d:	48 89 47 08          	mov    %rax,0x8(%rdi)
  401e11:	c3                   	retq   

0000000000401e12 <sigalrm_handler>:
  401e12:	48 83 ec 08          	sub    $0x8,%rsp
  401e16:	bf 20 58 60 00       	mov    $0x605820,%edi
  401e1b:	b8 00 00 00 00       	mov    $0x0,%eax
  401e20:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  401e27:	f2 ae                	repnz scas %es:(%rdi),%al
  401e29:	48 f7 d1             	not    %rcx
  401e2c:	48 8d 51 ff          	lea    -0x1(%rcx),%rdx
  401e30:	be 20 58 60 00       	mov    $0x605820,%esi
  401e35:	bf 02 00 00 00       	mov    $0x2,%edi
  401e3a:	e8 81 f0 ff ff       	callq  400ec0 <write@plt>
  401e3f:	bf 01 00 00 00       	mov    $0x1,%edi
  401e44:	e8 07 ef ff ff       	callq  400d50 <exit@plt>

0000000000401e49 <urlencode>:
  401e49:	41 54                	push   %r12
  401e4b:	55                   	push   %rbp
  401e4c:	53                   	push   %rbx
  401e4d:	48 83 ec 10          	sub    $0x10,%rsp
  401e51:	48 89 fb             	mov    %rdi,%rbx
  401e54:	48 89 f5             	mov    %rsi,%rbp
  401e57:	b8 00 00 00 00       	mov    $0x0,%eax
  401e5c:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  401e63:	f2 ae                	repnz scas %es:(%rdi),%al
  401e65:	48 f7 d1             	not    %rcx
  401e68:	8d 41 ff             	lea    -0x1(%rcx),%eax
  401e6b:	e9 93 00 00 00       	jmpq   401f03 <urlencode+0xba>
  401e70:	0f b6 13             	movzbl (%rbx),%edx
  401e73:	80 fa 2a             	cmp    $0x2a,%dl
  401e76:	0f 94 c1             	sete   %cl
  401e79:	80 fa 2d             	cmp    $0x2d,%dl
  401e7c:	0f 94 c0             	sete   %al
  401e7f:	08 c1                	or     %al,%cl
  401e81:	75 1f                	jne    401ea2 <urlencode+0x59>
  401e83:	80 fa 2e             	cmp    $0x2e,%dl
  401e86:	74 1a                	je     401ea2 <urlencode+0x59>
  401e88:	80 fa 5f             	cmp    $0x5f,%dl
  401e8b:	74 15                	je     401ea2 <urlencode+0x59>
  401e8d:	8d 42 d0             	lea    -0x30(%rdx),%eax
  401e90:	3c 09                	cmp    $0x9,%al
  401e92:	76 0e                	jbe    401ea2 <urlencode+0x59>
  401e94:	8d 42 bf             	lea    -0x41(%rdx),%eax
  401e97:	3c 19                	cmp    $0x19,%al
  401e99:	76 07                	jbe    401ea2 <urlencode+0x59>
  401e9b:	8d 42 9f             	lea    -0x61(%rdx),%eax
  401e9e:	3c 19                	cmp    $0x19,%al
  401ea0:	77 09                	ja     401eab <urlencode+0x62>
  401ea2:	88 55 00             	mov    %dl,0x0(%rbp)
  401ea5:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
  401ea9:	eb 51                	jmp    401efc <urlencode+0xb3>
  401eab:	80 fa 20             	cmp    $0x20,%dl
  401eae:	75 0a                	jne    401eba <urlencode+0x71>
  401eb0:	c6 45 00 2b          	movb   $0x2b,0x0(%rbp)
  401eb4:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
  401eb8:	eb 42                	jmp    401efc <urlencode+0xb3>
  401eba:	8d 42 e0             	lea    -0x20(%rdx),%eax
  401ebd:	3c 5f                	cmp    $0x5f,%al
  401ebf:	0f 96 c1             	setbe  %cl
  401ec2:	80 fa 09             	cmp    $0x9,%dl
  401ec5:	0f 94 c0             	sete   %al
  401ec8:	08 c1                	or     %al,%cl
  401eca:	74 45                	je     401f11 <urlencode+0xc8>
  401ecc:	0f b6 d2             	movzbl %dl,%edx
  401ecf:	be 68 33 40 00       	mov    $0x403368,%esi
  401ed4:	48 89 e7             	mov    %rsp,%rdi
  401ed7:	b8 00 00 00 00       	mov    $0x0,%eax
  401edc:	e8 0f ef ff ff       	callq  400df0 <sprintf@plt>
  401ee1:	0f b6 04 24          	movzbl (%rsp),%eax
  401ee5:	88 45 00             	mov    %al,0x0(%rbp)
  401ee8:	0f b6 44 24 01       	movzbl 0x1(%rsp),%eax
  401eed:	88 45 01             	mov    %al,0x1(%rbp)
  401ef0:	0f b6 44 24 02       	movzbl 0x2(%rsp),%eax
  401ef5:	88 45 02             	mov    %al,0x2(%rbp)
  401ef8:	48 8d 6d 03          	lea    0x3(%rbp),%rbp
  401efc:	48 83 c3 01          	add    $0x1,%rbx
  401f00:	44 89 e0             	mov    %r12d,%eax
  401f03:	44 8d 60 ff          	lea    -0x1(%rax),%r12d
  401f07:	85 c0                	test   %eax,%eax
  401f09:	0f 85 61 ff ff ff    	jne    401e70 <urlencode+0x27>
  401f0f:	eb 05                	jmp    401f16 <urlencode+0xcd>
  401f11:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401f16:	48 83 c4 10          	add    $0x10,%rsp
  401f1a:	5b                   	pop    %rbx
  401f1b:	5d                   	pop    %rbp
  401f1c:	41 5c                	pop    %r12
  401f1e:	c3                   	retq   

0000000000401f1f <rio_writen>:
  401f1f:	41 55                	push   %r13
  401f21:	41 54                	push   %r12
  401f23:	55                   	push   %rbp
  401f24:	53                   	push   %rbx
  401f25:	48 83 ec 08          	sub    $0x8,%rsp
  401f29:	41 89 fc             	mov    %edi,%r12d
  401f2c:	48 89 f5             	mov    %rsi,%rbp
  401f2f:	49 89 d5             	mov    %rdx,%r13
  401f32:	48 89 d3             	mov    %rdx,%rbx
  401f35:	eb 28                	jmp    401f5f <rio_writen+0x40>
  401f37:	48 89 da             	mov    %rbx,%rdx
  401f3a:	48 89 ee             	mov    %rbp,%rsi
  401f3d:	44 89 e7             	mov    %r12d,%edi
  401f40:	e8 7b ef ff ff       	callq  400ec0 <write@plt>
  401f45:	48 85 c0             	test   %rax,%rax
  401f48:	7f 0f                	jg     401f59 <rio_writen+0x3a>
  401f4a:	e8 31 ef ff ff       	callq  400e80 <__errno_location@plt>
  401f4f:	83 38 04             	cmpl   $0x4,(%rax)
  401f52:	75 15                	jne    401f69 <rio_writen+0x4a>
  401f54:	b8 00 00 00 00       	mov    $0x0,%eax
  401f59:	48 29 c3             	sub    %rax,%rbx
  401f5c:	48 01 c5             	add    %rax,%rbp
  401f5f:	48 85 db             	test   %rbx,%rbx
  401f62:	75 d3                	jne    401f37 <rio_writen+0x18>
  401f64:	4c 89 e8             	mov    %r13,%rax
  401f67:	eb 07                	jmp    401f70 <rio_writen+0x51>
  401f69:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  401f70:	48 83 c4 08          	add    $0x8,%rsp
  401f74:	5b                   	pop    %rbx
  401f75:	5d                   	pop    %rbp
  401f76:	41 5c                	pop    %r12
  401f78:	41 5d                	pop    %r13
  401f7a:	c3                   	retq   

0000000000401f7b <rio_read>:
  401f7b:	41 56                	push   %r14
  401f7d:	41 55                	push   %r13
  401f7f:	41 54                	push   %r12
  401f81:	55                   	push   %rbp
  401f82:	53                   	push   %rbx
  401f83:	48 89 fb             	mov    %rdi,%rbx
  401f86:	49 89 f6             	mov    %rsi,%r14
  401f89:	49 89 d5             	mov    %rdx,%r13
  401f8c:	4c 8d 67 10          	lea    0x10(%rdi),%r12
  401f90:	eb 2a                	jmp    401fbc <rio_read+0x41>
  401f92:	ba 00 20 00 00       	mov    $0x2000,%edx
  401f97:	4c 89 e6             	mov    %r12,%rsi
  401f9a:	8b 3b                	mov    (%rbx),%edi
  401f9c:	e8 cf ed ff ff       	callq  400d70 <read@plt>
  401fa1:	89 43 04             	mov    %eax,0x4(%rbx)
  401fa4:	85 c0                	test   %eax,%eax
  401fa6:	79 0c                	jns    401fb4 <rio_read+0x39>
  401fa8:	e8 d3 ee ff ff       	callq  400e80 <__errno_location@plt>
  401fad:	83 38 04             	cmpl   $0x4,(%rax)
  401fb0:	74 0a                	je     401fbc <rio_read+0x41>
  401fb2:	eb 37                	jmp    401feb <rio_read+0x70>
  401fb4:	85 c0                	test   %eax,%eax
  401fb6:	74 3c                	je     401ff4 <rio_read+0x79>
  401fb8:	4c 89 63 08          	mov    %r12,0x8(%rbx)
  401fbc:	8b 6b 04             	mov    0x4(%rbx),%ebp
  401fbf:	85 ed                	test   %ebp,%ebp
  401fc1:	7e cf                	jle    401f92 <rio_read+0x17>
  401fc3:	89 e8                	mov    %ebp,%eax
  401fc5:	4c 39 e8             	cmp    %r13,%rax
  401fc8:	72 03                	jb     401fcd <rio_read+0x52>
  401fca:	44 89 ed             	mov    %r13d,%ebp
  401fcd:	4c 63 e5             	movslq %ebp,%r12
  401fd0:	48 8b 73 08          	mov    0x8(%rbx),%rsi
  401fd4:	4c 89 e2             	mov    %r12,%rdx
  401fd7:	4c 89 f7             	mov    %r14,%rdi
  401fda:	e8 f1 ee ff ff       	callq  400ed0 <memcpy@plt>
  401fdf:	4c 01 63 08          	add    %r12,0x8(%rbx)
  401fe3:	29 6b 04             	sub    %ebp,0x4(%rbx)
  401fe6:	4c 89 e0             	mov    %r12,%rax
  401fe9:	eb 0e                	jmp    401ff9 <rio_read+0x7e>
  401feb:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  401ff2:	eb 05                	jmp    401ff9 <rio_read+0x7e>
  401ff4:	b8 00 00 00 00       	mov    $0x0,%eax
  401ff9:	5b                   	pop    %rbx
  401ffa:	5d                   	pop    %rbp
  401ffb:	41 5c                	pop    %r12
  401ffd:	41 5d                	pop    %r13
  401fff:	41 5e                	pop    %r14
  402001:	c3                   	retq   

0000000000402002 <rio_readlineb>:
  402002:	41 55                	push   %r13
  402004:	41 54                	push   %r12
  402006:	55                   	push   %rbp
  402007:	53                   	push   %rbx
  402008:	48 83 ec 18          	sub    $0x18,%rsp
  40200c:	49 89 fd             	mov    %rdi,%r13
  40200f:	48 89 f5             	mov    %rsi,%rbp
  402012:	49 89 d4             	mov    %rdx,%r12
  402015:	bb 01 00 00 00       	mov    $0x1,%ebx
  40201a:	eb 3f                	jmp    40205b <rio_readlineb+0x59>
  40201c:	ba 01 00 00 00       	mov    $0x1,%edx
  402021:	48 8d 74 24 0f       	lea    0xf(%rsp),%rsi
  402026:	4c 89 ef             	mov    %r13,%rdi
  402029:	e8 4d ff ff ff       	callq  401f7b <rio_read>
  40202e:	83 f8 01             	cmp    $0x1,%eax
  402031:	75 12                	jne    402045 <rio_readlineb+0x43>
  402033:	48 8d 55 01          	lea    0x1(%rbp),%rdx
  402037:	0f b6 44 24 0f       	movzbl 0xf(%rsp),%eax
  40203c:	88 45 00             	mov    %al,0x0(%rbp)
  40203f:	3c 0a                	cmp    $0xa,%al
  402041:	75 11                	jne    402054 <rio_readlineb+0x52>
  402043:	eb 1d                	jmp    402062 <rio_readlineb+0x60>
  402045:	85 c0                	test   %eax,%eax
  402047:	75 25                	jne    40206e <rio_readlineb+0x6c>
  402049:	48 83 fb 01          	cmp    $0x1,%rbx
  40204d:	0f 1f 00             	nopl   (%rax)
  402050:	75 13                	jne    402065 <rio_readlineb+0x63>
  402052:	eb 23                	jmp    402077 <rio_readlineb+0x75>
  402054:	48 83 c3 01          	add    $0x1,%rbx
  402058:	48 89 d5             	mov    %rdx,%rbp
  40205b:	4c 39 e3             	cmp    %r12,%rbx
  40205e:	72 bc                	jb     40201c <rio_readlineb+0x1a>
  402060:	eb 03                	jmp    402065 <rio_readlineb+0x63>
  402062:	48 89 d5             	mov    %rdx,%rbp
  402065:	c6 45 00 00          	movb   $0x0,0x0(%rbp)
  402069:	48 89 d8             	mov    %rbx,%rax
  40206c:	eb 0e                	jmp    40207c <rio_readlineb+0x7a>
  40206e:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  402075:	eb 05                	jmp    40207c <rio_readlineb+0x7a>
  402077:	b8 00 00 00 00       	mov    $0x0,%eax
  40207c:	48 83 c4 18          	add    $0x18,%rsp
  402080:	5b                   	pop    %rbx
  402081:	5d                   	pop    %rbp
  402082:	41 5c                	pop    %r12
  402084:	41 5d                	pop    %r13
  402086:	c3                   	retq   

0000000000402087 <submitr>:
  402087:	41 57                	push   %r15
  402089:	41 56                	push   %r14
  40208b:	41 55                	push   %r13
  40208d:	41 54                	push   %r12
  40208f:	55                   	push   %rbp
  402090:	53                   	push   %rbx
  402091:	48 81 ec 58 a0 00 00 	sub    $0xa058,%rsp
  402098:	49 89 fc             	mov    %rdi,%r12
  40209b:	89 74 24 1c          	mov    %esi,0x1c(%rsp)
  40209f:	48 89 54 24 10       	mov    %rdx,0x10(%rsp)
  4020a4:	49 89 cf             	mov    %rcx,%r15
  4020a7:	4d 89 c6             	mov    %r8,%r14
  4020aa:	4d 89 cd             	mov    %r9,%r13
  4020ad:	48 8b 9c 24 90 a0 00 	mov    0xa090(%rsp),%rbx
  4020b4:	00 
  4020b5:	c7 84 24 2c 20 00 00 	movl   $0x0,0x202c(%rsp)
  4020bc:	00 00 00 00 
  4020c0:	ba 00 00 00 00       	mov    $0x0,%edx
  4020c5:	be 01 00 00 00       	mov    $0x1,%esi
  4020ca:	bf 02 00 00 00       	mov    $0x2,%edi
  4020cf:	e8 7c ed ff ff       	callq  400e50 <socket@plt>
  4020d4:	89 c5                	mov    %eax,%ebp
  4020d6:	85 c0                	test   %eax,%eax
  4020d8:	79 4e                	jns    402128 <submitr+0xa1>
  4020da:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  4020e1:	3a 20 43 
  4020e4:	48 89 03             	mov    %rax,(%rbx)
  4020e7:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  4020ee:	20 75 6e 
  4020f1:	48 89 43 08          	mov    %rax,0x8(%rbx)
  4020f5:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  4020fc:	74 6f 20 
  4020ff:	48 89 43 10          	mov    %rax,0x10(%rbx)
  402103:	48 b8 63 72 65 61 74 	movabs $0x7320657461657263,%rax
  40210a:	65 20 73 
  40210d:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402111:	c7 43 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%rbx)
  402118:	66 c7 43 24 74 00    	movw   $0x74,0x24(%rbx)
  40211e:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402123:	e9 83 06 00 00       	jmpq   4027ab <submitr+0x724>
  402128:	4c 89 e7             	mov    %r12,%rdi
  40212b:	e8 e0 eb ff ff       	callq  400d10 <gethostbyname@plt>
  402130:	48 85 c0             	test   %rax,%rax
  402133:	75 75                	jne    4021aa <submitr+0x123>
  402135:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
  40213c:	3a 20 44 
  40213f:	48 89 03             	mov    %rax,(%rbx)
  402142:	48 b8 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rax
  402149:	20 75 6e 
  40214c:	48 89 43 08          	mov    %rax,0x8(%rbx)
  402150:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402157:	74 6f 20 
  40215a:	48 89 43 10          	mov    %rax,0x10(%rbx)
  40215e:	48 b8 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rax
  402165:	76 65 20 
  402168:	48 89 43 18          	mov    %rax,0x18(%rbx)
  40216c:	48 b8 41 75 74 6f 6c 	movabs $0x2062616c6f747541,%rax
  402173:	61 62 20 
  402176:	48 89 43 20          	mov    %rax,0x20(%rbx)
  40217a:	48 b8 73 65 72 76 65 	movabs $0x6120726576726573,%rax
  402181:	72 20 61 
  402184:	48 89 43 28          	mov    %rax,0x28(%rbx)
  402188:	c7 43 30 64 64 72 65 	movl   $0x65726464,0x30(%rbx)
  40218f:	66 c7 43 34 73 73    	movw   $0x7373,0x34(%rbx)
  402195:	c6 43 36 00          	movb   $0x0,0x36(%rbx)
  402199:	89 ef                	mov    %ebp,%edi
  40219b:	e8 60 eb ff ff       	callq  400d00 <close@plt>
  4021a0:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4021a5:	e9 01 06 00 00       	jmpq   4027ab <submitr+0x724>
  4021aa:	48 c7 84 24 40 a0 00 	movq   $0x0,0xa040(%rsp)
  4021b1:	00 00 00 00 00 
  4021b6:	48 c7 84 24 48 a0 00 	movq   $0x0,0xa048(%rsp)
  4021bd:	00 00 00 00 00 
  4021c2:	66 c7 84 24 40 a0 00 	movw   $0x2,0xa040(%rsp)
  4021c9:	00 02 00 
  4021cc:	48 8b 48 18          	mov    0x18(%rax),%rcx
  4021d0:	48 63 50 14          	movslq 0x14(%rax),%rdx
  4021d4:	48 8d b4 24 44 a0 00 	lea    0xa044(%rsp),%rsi
  4021db:	00 
  4021dc:	48 8b 39             	mov    (%rcx),%rdi
  4021df:	e8 dc eb ff ff       	callq  400dc0 <bcopy@plt>
  4021e4:	0f b7 44 24 1c       	movzwl 0x1c(%rsp),%eax
  4021e9:	66 c1 c8 08          	ror    $0x8,%ax
  4021ed:	66 89 84 24 42 a0 00 	mov    %ax,0xa042(%rsp)
  4021f4:	00 
  4021f5:	ba 10 00 00 00       	mov    $0x10,%edx
  4021fa:	48 8d b4 24 40 a0 00 	lea    0xa040(%rsp),%rsi
  402201:	00 
  402202:	89 ef                	mov    %ebp,%edi
  402204:	e8 07 ec ff ff       	callq  400e10 <connect@plt>
  402209:	85 c0                	test   %eax,%eax
  40220b:	79 67                	jns    402274 <submitr+0x1ed>
  40220d:	48 b8 45 72 72 6f 72 	movabs $0x55203a726f727245,%rax
  402214:	3a 20 55 
  402217:	48 89 03             	mov    %rax,(%rbx)
  40221a:	48 b8 6e 61 62 6c 65 	movabs $0x6f7420656c62616e,%rax
  402221:	20 74 6f 
  402224:	48 89 43 08          	mov    %rax,0x8(%rbx)
  402228:	48 b8 20 63 6f 6e 6e 	movabs $0x7463656e6e6f6320,%rax
  40222f:	65 63 74 
  402232:	48 89 43 10          	mov    %rax,0x10(%rbx)
  402236:	48 b8 20 74 6f 20 74 	movabs $0x20656874206f7420,%rax
  40223d:	68 65 20 
  402240:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402244:	48 b8 41 75 74 6f 6c 	movabs $0x2062616c6f747541,%rax
  40224b:	61 62 20 
  40224e:	48 89 43 20          	mov    %rax,0x20(%rbx)
  402252:	c7 43 28 73 65 72 76 	movl   $0x76726573,0x28(%rbx)
  402259:	66 c7 43 2c 65 72    	movw   $0x7265,0x2c(%rbx)
  40225f:	c6 43 2e 00          	movb   $0x0,0x2e(%rbx)
  402263:	89 ef                	mov    %ebp,%edi
  402265:	e8 96 ea ff ff       	callq  400d00 <close@plt>
  40226a:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  40226f:	e9 37 05 00 00       	jmpq   4027ab <submitr+0x724>
  402274:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
  40227b:	4c 89 ef             	mov    %r13,%rdi
  40227e:	b8 00 00 00 00       	mov    $0x0,%eax
  402283:	48 89 d1             	mov    %rdx,%rcx
  402286:	f2 ae                	repnz scas %es:(%rdi),%al
  402288:	48 f7 d1             	not    %rcx
  40228b:	48 89 ce             	mov    %rcx,%rsi
  40228e:	48 8b 7c 24 10       	mov    0x10(%rsp),%rdi
  402293:	48 89 d1             	mov    %rdx,%rcx
  402296:	f2 ae                	repnz scas %es:(%rdi),%al
  402298:	48 f7 d1             	not    %rcx
  40229b:	49 89 c8             	mov    %rcx,%r8
  40229e:	4c 89 ff             	mov    %r15,%rdi
  4022a1:	48 89 d1             	mov    %rdx,%rcx
  4022a4:	f2 ae                	repnz scas %es:(%rdi),%al
  4022a6:	49 29 c8             	sub    %rcx,%r8
  4022a9:	4c 89 f7             	mov    %r14,%rdi
  4022ac:	48 89 d1             	mov    %rdx,%rcx
  4022af:	f2 ae                	repnz scas %es:(%rdi),%al
  4022b1:	49 29 c8             	sub    %rcx,%r8
  4022b4:	48 8d 44 76 fd       	lea    -0x3(%rsi,%rsi,2),%rax
  4022b9:	49 8d 44 00 7b       	lea    0x7b(%r8,%rax,1),%rax
  4022be:	48 3d 00 20 00 00    	cmp    $0x2000,%rax
  4022c4:	76 72                	jbe    402338 <submitr+0x2b1>
  4022c6:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
  4022cd:	3a 20 52 
  4022d0:	48 89 03             	mov    %rax,(%rbx)
  4022d3:	48 b8 65 73 75 6c 74 	movabs $0x747320746c757365,%rax
  4022da:	20 73 74 
  4022dd:	48 89 43 08          	mov    %rax,0x8(%rbx)
  4022e1:	48 b8 72 69 6e 67 20 	movabs $0x6f6f7420676e6972,%rax
  4022e8:	74 6f 6f 
  4022eb:	48 89 43 10          	mov    %rax,0x10(%rbx)
  4022ef:	48 b8 20 6c 61 72 67 	movabs $0x202e656772616c20,%rax
  4022f6:	65 2e 20 
  4022f9:	48 89 43 18          	mov    %rax,0x18(%rbx)
  4022fd:	48 b8 49 6e 63 72 65 	movabs $0x6573616572636e49,%rax
  402304:	61 73 65 
  402307:	48 89 43 20          	mov    %rax,0x20(%rbx)
  40230b:	48 b8 20 53 55 42 4d 	movabs $0x5254494d42555320,%rax
  402312:	49 54 52 
  402315:	48 89 43 28          	mov    %rax,0x28(%rbx)
  402319:	48 b8 5f 4d 41 58 42 	movabs $0x46554258414d5f,%rax
  402320:	55 46 00 
  402323:	48 89 43 30          	mov    %rax,0x30(%rbx)
  402327:	89 ef                	mov    %ebp,%edi
  402329:	e8 d2 e9 ff ff       	callq  400d00 <close@plt>
  40232e:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402333:	e9 73 04 00 00       	jmpq   4027ab <submitr+0x724>
  402338:	48 8d b4 24 30 40 00 	lea    0x4030(%rsp),%rsi
  40233f:	00 
  402340:	b9 00 04 00 00       	mov    $0x400,%ecx
  402345:	b8 00 00 00 00       	mov    $0x0,%eax
  40234a:	48 89 f7             	mov    %rsi,%rdi
  40234d:	f3 48 ab             	rep stos %rax,%es:(%rdi)
  402350:	4c 89 ef             	mov    %r13,%rdi
  402353:	e8 f1 fa ff ff       	callq  401e49 <urlencode>
  402358:	85 c0                	test   %eax,%eax
  40235a:	0f 89 8a 00 00 00    	jns    4023ea <submitr+0x363>
  402360:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
  402367:	3a 20 52 
  40236a:	48 89 03             	mov    %rax,(%rbx)
  40236d:	48 b8 65 73 75 6c 74 	movabs $0x747320746c757365,%rax
  402374:	20 73 74 
  402377:	48 89 43 08          	mov    %rax,0x8(%rbx)
  40237b:	48 b8 72 69 6e 67 20 	movabs $0x6e6f6320676e6972,%rax
  402382:	63 6f 6e 
  402385:	48 89 43 10          	mov    %rax,0x10(%rbx)
  402389:	48 b8 74 61 69 6e 73 	movabs $0x6e6120736e696174,%rax
  402390:	20 61 6e 
  402393:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402397:	48 b8 20 69 6c 6c 65 	movabs $0x6c6167656c6c6920,%rax
  40239e:	67 61 6c 
  4023a1:	48 89 43 20          	mov    %rax,0x20(%rbx)
  4023a5:	48 b8 20 6f 72 20 75 	movabs $0x72706e7520726f20,%rax
  4023ac:	6e 70 72 
  4023af:	48 89 43 28          	mov    %rax,0x28(%rbx)
  4023b3:	48 b8 69 6e 74 61 62 	movabs $0x20656c6261746e69,%rax
  4023ba:	6c 65 20 
  4023bd:	48 89 43 30          	mov    %rax,0x30(%rbx)
  4023c1:	48 b8 63 68 61 72 61 	movabs $0x6574636172616863,%rax
  4023c8:	63 74 65 
  4023cb:	48 89 43 38          	mov    %rax,0x38(%rbx)
  4023cf:	66 c7 43 40 72 2e    	movw   $0x2e72,0x40(%rbx)
  4023d5:	c6 43 42 00          	movb   $0x0,0x42(%rbx)
  4023d9:	89 ef                	mov    %ebp,%edi
  4023db:	e8 20 e9 ff ff       	callq  400d00 <close@plt>
  4023e0:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4023e5:	e9 c1 03 00 00       	jmpq   4027ab <submitr+0x724>
  4023ea:	4c 89 24 24          	mov    %r12,(%rsp)
  4023ee:	4c 8d 8c 24 30 40 00 	lea    0x4030(%rsp),%r9
  4023f5:	00 
  4023f6:	4d 89 f8             	mov    %r15,%r8
  4023f9:	4c 89 f1             	mov    %r14,%rcx
  4023fc:	48 8b 54 24 10       	mov    0x10(%rsp),%rdx
  402401:	be b8 33 40 00       	mov    $0x4033b8,%esi
  402406:	48 8d bc 24 30 60 00 	lea    0x6030(%rsp),%rdi
  40240d:	00 
  40240e:	b8 00 00 00 00       	mov    $0x0,%eax
  402413:	e8 d8 e9 ff ff       	callq  400df0 <sprintf@plt>
  402418:	48 8d bc 24 30 60 00 	lea    0x6030(%rsp),%rdi
  40241f:	00 
  402420:	b8 00 00 00 00       	mov    $0x0,%eax
  402425:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  40242c:	f2 ae                	repnz scas %es:(%rdi),%al
  40242e:	48 f7 d1             	not    %rcx
  402431:	48 8d 51 ff          	lea    -0x1(%rcx),%rdx
  402435:	48 8d b4 24 30 60 00 	lea    0x6030(%rsp),%rsi
  40243c:	00 
  40243d:	89 ef                	mov    %ebp,%edi
  40243f:	e8 db fa ff ff       	callq  401f1f <rio_writen>
  402444:	48 85 c0             	test   %rax,%rax
  402447:	79 6b                	jns    4024b4 <submitr+0x42d>
  402449:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  402450:	3a 20 43 
  402453:	48 89 03             	mov    %rax,(%rbx)
  402456:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  40245d:	20 75 6e 
  402460:	48 89 43 08          	mov    %rax,0x8(%rbx)
  402464:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  40246b:	74 6f 20 
  40246e:	48 89 43 10          	mov    %rax,0x10(%rbx)
  402472:	48 b8 77 72 69 74 65 	movabs $0x6f74206574697277,%rax
  402479:	20 74 6f 
  40247c:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402480:	48 b8 20 74 68 65 20 	movabs $0x7475412065687420,%rax
  402487:	41 75 74 
  40248a:	48 89 43 20          	mov    %rax,0x20(%rbx)
  40248e:	48 b8 6f 6c 61 62 20 	movabs $0x7265732062616c6f,%rax
  402495:	73 65 72 
  402498:	48 89 43 28          	mov    %rax,0x28(%rbx)
  40249c:	c7 43 30 76 65 72 00 	movl   $0x726576,0x30(%rbx)
  4024a3:	89 ef                	mov    %ebp,%edi
  4024a5:	e8 56 e8 ff ff       	callq  400d00 <close@plt>
  4024aa:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4024af:	e9 f7 02 00 00       	jmpq   4027ab <submitr+0x724>
  4024b4:	89 ee                	mov    %ebp,%esi
  4024b6:	48 8d bc 24 30 80 00 	lea    0x8030(%rsp),%rdi
  4024bd:	00 
  4024be:	e8 3d f9 ff ff       	callq  401e00 <rio_readinitb>
  4024c3:	ba 00 20 00 00       	mov    $0x2000,%edx
  4024c8:	48 8d b4 24 30 60 00 	lea    0x6030(%rsp),%rsi
  4024cf:	00 
  4024d0:	48 8d bc 24 30 80 00 	lea    0x8030(%rsp),%rdi
  4024d7:	00 
  4024d8:	e8 25 fb ff ff       	callq  402002 <rio_readlineb>
  4024dd:	48 85 c0             	test   %rax,%rax
  4024e0:	7f 7f                	jg     402561 <submitr+0x4da>
  4024e2:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  4024e9:	3a 20 43 
  4024ec:	48 89 03             	mov    %rax,(%rbx)
  4024ef:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  4024f6:	20 75 6e 
  4024f9:	48 89 43 08          	mov    %rax,0x8(%rbx)
  4024fd:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402504:	74 6f 20 
  402507:	48 89 43 10          	mov    %rax,0x10(%rbx)
  40250b:	48 b8 72 65 61 64 20 	movabs $0x7269662064616572,%rax
  402512:	66 69 72 
  402515:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402519:	48 b8 73 74 20 68 65 	movabs $0x6564616568207473,%rax
  402520:	61 64 65 
  402523:	48 89 43 20          	mov    %rax,0x20(%rbx)
  402527:	48 b8 72 20 66 72 6f 	movabs $0x41206d6f72662072,%rax
  40252e:	6d 20 41 
  402531:	48 89 43 28          	mov    %rax,0x28(%rbx)
  402535:	48 b8 75 74 6f 6c 61 	movabs $0x732062616c6f7475,%rax
  40253c:	62 20 73 
  40253f:	48 89 43 30          	mov    %rax,0x30(%rbx)
  402543:	c7 43 38 65 72 76 65 	movl   $0x65767265,0x38(%rbx)
  40254a:	66 c7 43 3c 72 00    	movw   $0x72,0x3c(%rbx)
  402550:	89 ef                	mov    %ebp,%edi
  402552:	e8 a9 e7 ff ff       	callq  400d00 <close@plt>
  402557:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  40255c:	e9 4a 02 00 00       	jmpq   4027ab <submitr+0x724>
  402561:	4c 8d 44 24 20       	lea    0x20(%rsp),%r8
  402566:	48 8d 8c 24 2c 20 00 	lea    0x202c(%rsp),%rcx
  40256d:	00 
  40256e:	48 8d 94 24 30 20 00 	lea    0x2030(%rsp),%rdx
  402575:	00 
  402576:	be 6f 33 40 00       	mov    $0x40336f,%esi
  40257b:	48 8d bc 24 30 60 00 	lea    0x6030(%rsp),%rdi
  402582:	00 
  402583:	b8 00 00 00 00       	mov    $0x0,%eax
  402588:	e8 b3 e7 ff ff       	callq  400d40 <__isoc99_sscanf@plt>
  40258d:	e9 95 00 00 00       	jmpq   402627 <submitr+0x5a0>
  402592:	ba 00 20 00 00       	mov    $0x2000,%edx
  402597:	48 8d b4 24 30 60 00 	lea    0x6030(%rsp),%rsi
  40259e:	00 
  40259f:	48 8d bc 24 30 80 00 	lea    0x8030(%rsp),%rdi
  4025a6:	00 
  4025a7:	e8 56 fa ff ff       	callq  402002 <rio_readlineb>
  4025ac:	48 85 c0             	test   %rax,%rax
  4025af:	7f 76                	jg     402627 <submitr+0x5a0>
  4025b1:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  4025b8:	3a 20 43 
  4025bb:	48 89 03             	mov    %rax,(%rbx)
  4025be:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  4025c5:	20 75 6e 
  4025c8:	48 89 43 08          	mov    %rax,0x8(%rbx)
  4025cc:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  4025d3:	74 6f 20 
  4025d6:	48 89 43 10          	mov    %rax,0x10(%rbx)
  4025da:	48 b8 72 65 61 64 20 	movabs $0x6165682064616572,%rax
  4025e1:	68 65 61 
  4025e4:	48 89 43 18          	mov    %rax,0x18(%rbx)
  4025e8:	48 b8 64 65 72 73 20 	movabs $0x6f72662073726564,%rax
  4025ef:	66 72 6f 
  4025f2:	48 89 43 20          	mov    %rax,0x20(%rbx)
  4025f6:	48 b8 6d 20 41 75 74 	movabs $0x616c6f747541206d,%rax
  4025fd:	6f 6c 61 
  402600:	48 89 43 28          	mov    %rax,0x28(%rbx)
  402604:	48 b8 62 20 73 65 72 	movabs $0x7265767265732062,%rax
  40260b:	76 65 72 
  40260e:	48 89 43 30          	mov    %rax,0x30(%rbx)
  402612:	c6 43 38 00          	movb   $0x0,0x38(%rbx)
  402616:	89 ef                	mov    %ebp,%edi
  402618:	e8 e3 e6 ff ff       	callq  400d00 <close@plt>
  40261d:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402622:	e9 84 01 00 00       	jmpq   4027ab <submitr+0x724>
  402627:	0f b6 84 24 30 60 00 	movzbl 0x6030(%rsp),%eax
  40262e:	00 
  40262f:	83 e8 0d             	sub    $0xd,%eax
  402632:	75 15                	jne    402649 <submitr+0x5c2>
  402634:	0f b6 84 24 31 60 00 	movzbl 0x6031(%rsp),%eax
  40263b:	00 
  40263c:	83 e8 0a             	sub    $0xa,%eax
  40263f:	75 08                	jne    402649 <submitr+0x5c2>
  402641:	0f b6 84 24 32 60 00 	movzbl 0x6032(%rsp),%eax
  402648:	00 
  402649:	85 c0                	test   %eax,%eax
  40264b:	0f 85 41 ff ff ff    	jne    402592 <submitr+0x50b>
  402651:	ba 00 20 00 00       	mov    $0x2000,%edx
  402656:	48 8d b4 24 30 60 00 	lea    0x6030(%rsp),%rsi
  40265d:	00 
  40265e:	48 8d bc 24 30 80 00 	lea    0x8030(%rsp),%rdi
  402665:	00 
  402666:	e8 97 f9 ff ff       	callq  402002 <rio_readlineb>
  40266b:	48 85 c0             	test   %rax,%rax
  40266e:	0f 8f 80 00 00 00    	jg     4026f4 <submitr+0x66d>
  402674:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  40267b:	3a 20 43 
  40267e:	48 89 03             	mov    %rax,(%rbx)
  402681:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  402688:	20 75 6e 
  40268b:	48 89 43 08          	mov    %rax,0x8(%rbx)
  40268f:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402696:	74 6f 20 
  402699:	48 89 43 10          	mov    %rax,0x10(%rbx)
  40269d:	48 b8 72 65 61 64 20 	movabs $0x6174732064616572,%rax
  4026a4:	73 74 61 
  4026a7:	48 89 43 18          	mov    %rax,0x18(%rbx)
  4026ab:	48 b8 74 75 73 20 6d 	movabs $0x7373656d20737574,%rax
  4026b2:	65 73 73 
  4026b5:	48 89 43 20          	mov    %rax,0x20(%rbx)
  4026b9:	48 b8 61 67 65 20 66 	movabs $0x6d6f726620656761,%rax
  4026c0:	72 6f 6d 
  4026c3:	48 89 43 28          	mov    %rax,0x28(%rbx)
  4026c7:	48 b8 20 41 75 74 6f 	movabs $0x62616c6f74754120,%rax
  4026ce:	6c 61 62 
  4026d1:	48 89 43 30          	mov    %rax,0x30(%rbx)
  4026d5:	48 b8 20 73 65 72 76 	movabs $0x72657672657320,%rax
  4026dc:	65 72 00 
  4026df:	48 89 43 38          	mov    %rax,0x38(%rbx)
  4026e3:	89 ef                	mov    %ebp,%edi
  4026e5:	e8 16 e6 ff ff       	callq  400d00 <close@plt>
  4026ea:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4026ef:	e9 b7 00 00 00       	jmpq   4027ab <submitr+0x724>
  4026f4:	8b 94 24 2c 20 00 00 	mov    0x202c(%rsp),%edx
  4026fb:	81 fa c8 00 00 00    	cmp    $0xc8,%edx
  402701:	74 28                	je     40272b <submitr+0x6a4>
  402703:	48 8d 4c 24 20       	lea    0x20(%rsp),%rcx
  402708:	be 18 34 40 00       	mov    $0x403418,%esi
  40270d:	48 89 df             	mov    %rbx,%rdi
  402710:	b8 00 00 00 00       	mov    $0x0,%eax
  402715:	e8 d6 e6 ff ff       	callq  400df0 <sprintf@plt>
  40271a:	89 ef                	mov    %ebp,%edi
  40271c:	e8 df e5 ff ff       	callq  400d00 <close@plt>
  402721:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402726:	e9 80 00 00 00       	jmpq   4027ab <submitr+0x724>
  40272b:	48 8d b4 24 30 60 00 	lea    0x6030(%rsp),%rsi
  402732:	00 
  402733:	48 89 df             	mov    %rbx,%rdi
  402736:	e8 55 e7 ff ff       	callq  400e90 <strcpy@plt>
  40273b:	89 ef                	mov    %ebp,%edi
  40273d:	e8 be e5 ff ff       	callq  400d00 <close@plt>
  402742:	0f b6 03             	movzbl (%rbx),%eax
  402745:	83 e8 4f             	sub    $0x4f,%eax
  402748:	75 18                	jne    402762 <submitr+0x6db>
  40274a:	0f b6 53 01          	movzbl 0x1(%rbx),%edx
  40274e:	83 ea 4b             	sub    $0x4b,%edx
  402751:	75 11                	jne    402764 <submitr+0x6dd>
  402753:	0f b6 53 02          	movzbl 0x2(%rbx),%edx
  402757:	83 ea 0a             	sub    $0xa,%edx
  40275a:	75 08                	jne    402764 <submitr+0x6dd>
  40275c:	0f b6 53 03          	movzbl 0x3(%rbx),%edx
  402760:	eb 02                	jmp    402764 <submitr+0x6dd>
  402762:	89 c2                	mov    %eax,%edx
  402764:	85 d2                	test   %edx,%edx
  402766:	74 30                	je     402798 <submitr+0x711>
  402768:	bf 80 33 40 00       	mov    $0x403380,%edi
  40276d:	b9 05 00 00 00       	mov    $0x5,%ecx
  402772:	48 89 de             	mov    %rbx,%rsi
  402775:	f3 a6                	repz cmpsb %es:(%rdi),%ds:(%rsi)
  402777:	0f 97 c1             	seta   %cl
  40277a:	0f 92 c2             	setb   %dl
  40277d:	38 d1                	cmp    %dl,%cl
  40277f:	74 1e                	je     40279f <submitr+0x718>
  402781:	85 c0                	test   %eax,%eax
  402783:	75 0d                	jne    402792 <submitr+0x70b>
  402785:	0f b6 43 01          	movzbl 0x1(%rbx),%eax
  402789:	83 e8 4b             	sub    $0x4b,%eax
  40278c:	75 04                	jne    402792 <submitr+0x70b>
  40278e:	0f b6 43 02          	movzbl 0x2(%rbx),%eax
  402792:	85 c0                	test   %eax,%eax
  402794:	75 10                	jne    4027a6 <submitr+0x71f>
  402796:	eb 13                	jmp    4027ab <submitr+0x724>
  402798:	b8 00 00 00 00       	mov    $0x0,%eax
  40279d:	eb 0c                	jmp    4027ab <submitr+0x724>
  40279f:	b8 00 00 00 00       	mov    $0x0,%eax
  4027a4:	eb 05                	jmp    4027ab <submitr+0x724>
  4027a6:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4027ab:	48 81 c4 58 a0 00 00 	add    $0xa058,%rsp
  4027b2:	5b                   	pop    %rbx
  4027b3:	5d                   	pop    %rbp
  4027b4:	41 5c                	pop    %r12
  4027b6:	41 5d                	pop    %r13
  4027b8:	41 5e                	pop    %r14
  4027ba:	41 5f                	pop    %r15
  4027bc:	c3                   	retq   

00000000004027bd <init_timeout>:
  4027bd:	53                   	push   %rbx
  4027be:	89 fb                	mov    %edi,%ebx
  4027c0:	85 ff                	test   %edi,%edi
  4027c2:	74 3a                	je     4027fe <init_timeout+0x41>
  4027c4:	85 ff                	test   %edi,%edi
  4027c6:	79 05                	jns    4027cd <init_timeout+0x10>
  4027c8:	bb 00 00 00 00       	mov    $0x0,%ebx
  4027cd:	89 d9                	mov    %ebx,%ecx
  4027cf:	ba 48 34 40 00       	mov    $0x403448,%edx
  4027d4:	be 40 00 00 00       	mov    $0x40,%esi
  4027d9:	bf 20 58 60 00       	mov    $0x605820,%edi
  4027de:	b8 00 00 00 00       	mov    $0x0,%eax
  4027e3:	e8 08 e5 ff ff       	callq  400cf0 <snprintf@plt>
  4027e8:	be 12 1e 40 00       	mov    $0x401e12,%esi
  4027ed:	bf 0e 00 00 00       	mov    $0xe,%edi
  4027f2:	e8 49 e6 ff ff       	callq  400e40 <signal@plt>
  4027f7:	89 df                	mov    %ebx,%edi
  4027f9:	e8 72 e6 ff ff       	callq  400e70 <alarm@plt>
  4027fe:	5b                   	pop    %rbx
  4027ff:	c3                   	retq   

0000000000402800 <init_driver>:
  402800:	55                   	push   %rbp
  402801:	53                   	push   %rbx
  402802:	48 83 ec 18          	sub    $0x18,%rsp
  402806:	48 89 fd             	mov    %rdi,%rbp
  402809:	be 01 00 00 00       	mov    $0x1,%esi
  40280e:	bf 0d 00 00 00       	mov    $0xd,%edi
  402813:	e8 28 e6 ff ff       	callq  400e40 <signal@plt>
  402818:	be 01 00 00 00       	mov    $0x1,%esi
  40281d:	bf 1d 00 00 00       	mov    $0x1d,%edi
  402822:	e8 19 e6 ff ff       	callq  400e40 <signal@plt>
  402827:	be 01 00 00 00       	mov    $0x1,%esi
  40282c:	bf 1d 00 00 00       	mov    $0x1d,%edi
  402831:	e8 0a e6 ff ff       	callq  400e40 <signal@plt>
  402836:	ba 00 00 00 00       	mov    $0x0,%edx
  40283b:	be 01 00 00 00       	mov    $0x1,%esi
  402840:	bf 02 00 00 00       	mov    $0x2,%edi
  402845:	e8 06 e6 ff ff       	callq  400e50 <socket@plt>
  40284a:	89 c3                	mov    %eax,%ebx
  40284c:	85 c0                	test   %eax,%eax
  40284e:	79 4f                	jns    40289f <init_driver+0x9f>
  402850:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  402857:	3a 20 43 
  40285a:	48 89 45 00          	mov    %rax,0x0(%rbp)
  40285e:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  402865:	20 75 6e 
  402868:	48 89 45 08          	mov    %rax,0x8(%rbp)
  40286c:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402873:	74 6f 20 
  402876:	48 89 45 10          	mov    %rax,0x10(%rbp)
  40287a:	48 b8 63 72 65 61 74 	movabs $0x7320657461657263,%rax
  402881:	65 20 73 
  402884:	48 89 45 18          	mov    %rax,0x18(%rbp)
  402888:	c7 45 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%rbp)
  40288f:	66 c7 45 24 74 00    	movw   $0x74,0x24(%rbp)
  402895:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  40289a:	e9 23 01 00 00       	jmpq   4029c2 <init_driver+0x1c2>
  40289f:	bf 85 33 40 00       	mov    $0x403385,%edi
  4028a4:	e8 67 e4 ff ff       	callq  400d10 <gethostbyname@plt>
  4028a9:	48 85 c0             	test   %rax,%rax
  4028ac:	75 68                	jne    402916 <init_driver+0x116>
  4028ae:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
  4028b5:	3a 20 44 
  4028b8:	48 89 45 00          	mov    %rax,0x0(%rbp)
  4028bc:	48 b8 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rax
  4028c3:	20 75 6e 
  4028c6:	48 89 45 08          	mov    %rax,0x8(%rbp)
  4028ca:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  4028d1:	74 6f 20 
  4028d4:	48 89 45 10          	mov    %rax,0x10(%rbp)
  4028d8:	48 b8 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rax
  4028df:	76 65 20 
  4028e2:	48 89 45 18          	mov    %rax,0x18(%rbp)
  4028e6:	48 b8 73 65 72 76 65 	movabs $0x6120726576726573,%rax
  4028ed:	72 20 61 
  4028f0:	48 89 45 20          	mov    %rax,0x20(%rbp)
  4028f4:	c7 45 28 64 64 72 65 	movl   $0x65726464,0x28(%rbp)
  4028fb:	66 c7 45 2c 73 73    	movw   $0x7373,0x2c(%rbp)
  402901:	c6 45 2e 00          	movb   $0x0,0x2e(%rbp)
  402905:	89 df                	mov    %ebx,%edi
  402907:	e8 f4 e3 ff ff       	callq  400d00 <close@plt>
  40290c:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402911:	e9 ac 00 00 00       	jmpq   4029c2 <init_driver+0x1c2>
  402916:	48 c7 04 24 00 00 00 	movq   $0x0,(%rsp)
  40291d:	00 
  40291e:	48 c7 44 24 08 00 00 	movq   $0x0,0x8(%rsp)
  402925:	00 00 
  402927:	66 c7 04 24 02 00    	movw   $0x2,(%rsp)
  40292d:	48 8b 48 18          	mov    0x18(%rax),%rcx
  402931:	48 63 50 14          	movslq 0x14(%rax),%rdx
  402935:	48 8d 74 24 04       	lea    0x4(%rsp),%rsi
  40293a:	48 8b 39             	mov    (%rcx),%rdi
  40293d:	e8 7e e4 ff ff       	callq  400dc0 <bcopy@plt>
  402942:	66 c7 44 24 02 00 50 	movw   $0x5000,0x2(%rsp)
  402949:	ba 10 00 00 00       	mov    $0x10,%edx
  40294e:	48 89 e6             	mov    %rsp,%rsi
  402951:	89 df                	mov    %ebx,%edi
  402953:	e8 b8 e4 ff ff       	callq  400e10 <connect@plt>
  402958:	85 c0                	test   %eax,%eax
  40295a:	79 50                	jns    4029ac <init_driver+0x1ac>
  40295c:	48 b8 45 72 72 6f 72 	movabs $0x55203a726f727245,%rax
  402963:	3a 20 55 
  402966:	48 89 45 00          	mov    %rax,0x0(%rbp)
  40296a:	48 b8 6e 61 62 6c 65 	movabs $0x6f7420656c62616e,%rax
  402971:	20 74 6f 
  402974:	48 89 45 08          	mov    %rax,0x8(%rbp)
  402978:	48 b8 20 63 6f 6e 6e 	movabs $0x7463656e6e6f6320,%rax
  40297f:	65 63 74 
  402982:	48 89 45 10          	mov    %rax,0x10(%rbp)
  402986:	48 b8 20 74 6f 20 73 	movabs $0x76726573206f7420,%rax
  40298d:	65 72 76 
  402990:	48 89 45 18          	mov    %rax,0x18(%rbp)
  402994:	66 c7 45 20 65 72    	movw   $0x7265,0x20(%rbp)
  40299a:	c6 45 22 00          	movb   $0x0,0x22(%rbp)
  40299e:	89 df                	mov    %ebx,%edi
  4029a0:	e8 5b e3 ff ff       	callq  400d00 <close@plt>
  4029a5:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4029aa:	eb 16                	jmp    4029c2 <init_driver+0x1c2>
  4029ac:	89 df                	mov    %ebx,%edi
  4029ae:	e8 4d e3 ff ff       	callq  400d00 <close@plt>
  4029b3:	66 c7 45 00 4f 4b    	movw   $0x4b4f,0x0(%rbp)
  4029b9:	c6 45 02 00          	movb   $0x0,0x2(%rbp)
  4029bd:	b8 00 00 00 00       	mov    $0x0,%eax
  4029c2:	48 83 c4 18          	add    $0x18,%rsp
  4029c6:	5b                   	pop    %rbx
  4029c7:	5d                   	pop    %rbp
  4029c8:	c3                   	retq   

00000000004029c9 <driver_post>:
  4029c9:	53                   	push   %rbx
  4029ca:	48 83 ec 10          	sub    $0x10,%rsp
  4029ce:	4c 89 cb             	mov    %r9,%rbx
  4029d1:	45 85 c0             	test   %r8d,%r8d
  4029d4:	74 22                	je     4029f8 <driver_post+0x2f>
  4029d6:	48 89 ce             	mov    %rcx,%rsi
  4029d9:	bf 9c 33 40 00       	mov    $0x40339c,%edi
  4029de:	b8 00 00 00 00       	mov    $0x0,%eax
  4029e3:	e8 f8 e2 ff ff       	callq  400ce0 <printf@plt>
  4029e8:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
  4029ed:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
  4029f1:	b8 00 00 00 00       	mov    $0x0,%eax
  4029f6:	eb 39                	jmp    402a31 <driver_post+0x68>
  4029f8:	48 85 ff             	test   %rdi,%rdi
  4029fb:	74 26                	je     402a23 <driver_post+0x5a>
  4029fd:	80 3f 00             	cmpb   $0x0,(%rdi)
  402a00:	74 21                	je     402a23 <driver_post+0x5a>
  402a02:	4c 89 0c 24          	mov    %r9,(%rsp)
  402a06:	49 89 c9             	mov    %rcx,%r9
  402a09:	49 89 d0             	mov    %rdx,%r8
  402a0c:	48 89 f9             	mov    %rdi,%rcx
  402a0f:	48 89 f2             	mov    %rsi,%rdx
  402a12:	be 50 00 00 00       	mov    $0x50,%esi
  402a17:	bf 85 33 40 00       	mov    $0x403385,%edi
  402a1c:	e8 66 f6 ff ff       	callq  402087 <submitr>
  402a21:	eb 0e                	jmp    402a31 <driver_post+0x68>
  402a23:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
  402a28:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
  402a2c:	b8 00 00 00 00       	mov    $0x0,%eax
  402a31:	48 83 c4 10          	add    $0x10,%rsp
  402a35:	5b                   	pop    %rbx
  402a36:	c3                   	retq   
  402a37:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  402a3e:	00 00 

0000000000402a40 <__libc_csu_init>:
  402a40:	41 57                	push   %r15
  402a42:	41 89 ff             	mov    %edi,%r15d
  402a45:	41 56                	push   %r14
  402a47:	49 89 f6             	mov    %rsi,%r14
  402a4a:	41 55                	push   %r13
  402a4c:	49 89 d5             	mov    %rdx,%r13
  402a4f:	41 54                	push   %r12
  402a51:	4c 8d 25 98 13 20 00 	lea    0x201398(%rip),%r12        # 603df0 <__frame_dummy_init_array_entry>
  402a58:	55                   	push   %rbp
  402a59:	48 8d 2d 98 13 20 00 	lea    0x201398(%rip),%rbp        # 603df8 <__init_array_end>
  402a60:	53                   	push   %rbx
  402a61:	4c 29 e5             	sub    %r12,%rbp
  402a64:	31 db                	xor    %ebx,%ebx
  402a66:	48 c1 fd 03          	sar    $0x3,%rbp
  402a6a:	48 83 ec 08          	sub    $0x8,%rsp
  402a6e:	e8 3d e2 ff ff       	callq  400cb0 <_init>
  402a73:	48 85 ed             	test   %rbp,%rbp
  402a76:	74 1e                	je     402a96 <__libc_csu_init+0x56>
  402a78:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  402a7f:	00 
  402a80:	4c 89 ea             	mov    %r13,%rdx
  402a83:	4c 89 f6             	mov    %r14,%rsi
  402a86:	44 89 ff             	mov    %r15d,%edi
  402a89:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  402a8d:	48 83 c3 01          	add    $0x1,%rbx
  402a91:	48 39 eb             	cmp    %rbp,%rbx
  402a94:	75 ea                	jne    402a80 <__libc_csu_init+0x40>
  402a96:	48 83 c4 08          	add    $0x8,%rsp
  402a9a:	5b                   	pop    %rbx
  402a9b:	5d                   	pop    %rbp
  402a9c:	41 5c                	pop    %r12
  402a9e:	41 5d                	pop    %r13
  402aa0:	41 5e                	pop    %r14
  402aa2:	41 5f                	pop    %r15
  402aa4:	c3                   	retq   
  402aa5:	90                   	nop
  402aa6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  402aad:	00 00 00 

0000000000402ab0 <__libc_csu_fini>:
  402ab0:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000402ab4 <_fini>:
  402ab4:	48 83 ec 08          	sub    $0x8,%rsp
  402ab8:	48 83 c4 08          	add    $0x8,%rsp
  402abc:	c3                   	retq   
