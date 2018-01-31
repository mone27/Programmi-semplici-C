bin/disp -p abcd     | bin/cmp src/test/disp/disp_p_abcd.txt
bin/disp -p abcd 4   | bin/cmp src/test/disp/disp_p_abcd.txt
bin/disp -prr abcd   | bin/cmp src/test/disp/disp_p_abcd.txt
bin/disp -prr abcd 4 | bin/cmp src/test/disp/disp_p_abcd.txt
bin/disp -c abcdef 3   | bin/cmp src/test/disp/disp_c_abcdef_3.txt
bin/disp -crr abcdef 3 | bin/cmp src/test/disp/disp_c_abcdef_3.txt
bin/disp -p abcdef 2   | bin/cmp src/test/disp/disp_p_abcdef_2.txt
bin/disp -prr abcdef 2 | bin/cmp src/test/disp/disp_p_abcdef_2.txt
bin/disp -pr abc          | bin/cmp src/test/disp/disp_pr_abc.txt
bin/disp -pr abc 3        | bin/cmp src/test/disp/disp_pr_abc.txt
bin/disp -prr aaabbbccc 3 | bin/cmp src/test/disp/disp_pr_abc.txt
bin/disp -pr abcde 2       | bin/cmp src/test/disp/disp_pr_abcde_2.txt
bin/disp -prr aabbccddee 2 | bin/cmp src/test/disp/disp_pr_abcde_2.txt
bin/disp -cr abcd                | bin/cmp src/test/disp/disp_cr_abcd.txt
bin/disp -cr abcd 4              | bin/cmp src/test/disp/disp_cr_abcd.txt
bin/disp -crr aaaabbbbccccdddd 4 | bin/cmp src/test/disp/disp_cr_abcd.txt
bin/disp -cr abcde 3            | bin/cmp src/test/disp/disp_cr_abcde_3.txt
bin/disp -crr aaabbbcccdddeee 3 | bin/cmp src/test/disp/disp_cr_abcde_3.txt
bin/disp -crr aabbbcdddee 3 | bin/cmp src/test/disp/disp_crr_aabbbcdddee_3.txt
bin/disp -prr abbbccd 3 | bin/cmp src/test/disp/disp_prr_abbbccd_3.txt
