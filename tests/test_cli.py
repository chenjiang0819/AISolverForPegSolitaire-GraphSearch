from pathlib import Path
import os,subprocess,unittest,re
ROOT=Path(__file__).resolve().parents[1]
PROGRAM=os.environ.get('PROGRAM',str(ROOT/'pegsol'))
class CliTests(unittest.TestCase):
    def run_cli(self,args,valid=True):
        r=subprocess.run([PROGRAM,*args],input='',capture_output=True,text=True,timeout=10)
        self.assertNotIn('AddressSanitizer',r.stderr);self.assertNotIn('runtime error:',r.stderr)
        self.assertEqual(r.returncode==0,valid,r.stderr);return r.stdout
    def test_arguments_and_eof(self):
        for args in [[],['-1'],['9'],['99999999999999999999'],['a'],['0','bad'],['0','AI','0'],['0','AI','no'],['0','AI','1','wrong']]:self.run_cli(args,False)
        self.run_cli(['0'])
    def test_all_layouts_and_budget(self):
        for level in range(9):
            out=self.run_cli([str(level),'AI','100'])
            self.assertLessEqual(int(re.search(r'Expanded nodes: (\d+)',out)[1]),100)
        for _ in range(3):self.assertIn('Number of Pegs Left: 1',self.run_cli(['0','AI','100']))
if __name__=='__main__':unittest.main()
