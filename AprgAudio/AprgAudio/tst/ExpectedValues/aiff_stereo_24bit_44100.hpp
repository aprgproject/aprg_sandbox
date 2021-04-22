#include <vector>

namespace aiff_stereo_24bit_44100 { 

int numSamplesPerChannel = 352800;
int bitDepth = 24;
int sampleRate = 44100;
int numChannels = 2;

std::vector<std::vector<double>> testBuffer = {{0.0, 2.38418579102e-07, 1.78813934326e-06, 5.48362731934e-06, 1.32322311401e-05, 2.4676322937e-05, 4.19616699219e-05, 6.41345977783e-05, -0.000546932220459, -0.00276494026184, -0.00190901756287, 0.00353264808655, 0.00281715393066, 0.000813603401184, 0.000235080718994, -0.00211131572723, 0.000146865844727, 0.0147784948349, 0.04538834095, 0.0452077388763, -0.00408184528351, -0.0630596876144, -0.0665360689163, -0.029284119606, -0.0248633623123, -0.0178025960922, -0.0138409137726, 0.0193150043488, 0.0856702327728, 0.0424548387527, -0.0414769649506, -0.028416633606, 0.00969433784485, 0.0199648141861, -0.00319063663483, -0.0531134605408, -0.0273231267929, 0.066423535347, 0.102694034576, 0.102532505989, 0.0876024961472, 0.0381640195847, 0.0541303157806, 0.0822384357452, 0.0501530170441, 0.0265548229218, 0.0518268346786, 0.0546052455902, -0.000580906867981, 0.03950548172, 0.105013489723, 0.0574150085449, 0.0132118463516, 0.0348595380783, 0.0550781488419, 0.0467036962509, -0.0168364048004, -0.0915704965591, -0.0817813873291, 0.00328934192657, 0.0444622039795, -0.056557059288, -0.13708782196, -0.088475227356, -0.0222489833832, -0.0152742862701, -0.0281835794449, -0.0386518239975, -0.0558116436005, -0.0432333946228, -0.0281615257263, -0.0176116228104, -0.0335260629654, -0.0827516317368, -0.106855988503, -0.103455543518, -0.119733572006, -0.09033203125, -0.0443712472916, -0.0946414470673, -0.117385387421, -0.105598926544, -0.081170797348, -0.0644904375076, -0.128262519836, -0.154856324196, -0.0441133975983, 0.023441195488, -0.0313950777054, -0.0108451843262, 0.00420999526978, -0.0479471683502, -0.0966053009033, -0.0793578624725, 0.0220893621445, 0.0645458698273, 0.00624227523804, -0.053893327713, 0.0092670917511, 0.0192720890045, -0.124576687813, -0.169452786446, -0.0690652132034, -0.0180199146271, -0.00901186466217, 0.0409076213837, 0.0557831525803, 0.0454059839249, -0.0172625780106, -0.0948166847229, -0.0946356058121, -0.0850372314453, -0.0704460144043, 0.044732093811, 0.140439033508, 0.0615311861038, -0.00177681446075, 0.0507057905197, 0.0514181852341, -0.0261795520782, 0.00133180618286, 0.103703141212, 0.120507955551, 0.135626196861, 0.197693109512, 0.14523100853, -0.0105806589127, -0.0808025598526, -0.0255132913589, 0.0731819868088, 0.114405274391, 0.14054787159, 0.198596000671, 0.226037859917, 0.259689688683, 0.275172233582, 0.218914031982, 0.172498583794, 0.105105757713, 0.0212075710297, 0.0335985422134, 0.115469455719, 0.162777781487, 0.136108994484, 0.11561858654, 0.158184766769, 0.152153491974, 0.00384950637817, -0.0306369066238, 0.130526065826, 0.184431672096, 0.173121213913, 0.154246211052, 0.0742192268372, 0.0512671470642, 0.0389198064804, 0.022106051445, 0.0128885507584, -0.00770902633667, 0.029566526413, 0.0306620597839, -0.0271542072296, 0.0406365394592, 0.163035392761, 0.113360285759, -0.0299204587936, -0.0788315534592, -0.0539022684097, -0.0668505430222, -0.115531206131, -0.144212961197, -0.155148148537, -0.235722303391, -0.338488221169, -0.308323502541, -0.20271229744, -0.135675907135, -0.153830170631, -0.169016599655, -0.147540569305, -0.187671303749, -0.235207676888, -0.227528691292, -0.198186039925, -0.19126868248, -0.181129336357, -0.155988335609, -0.150921821594, -0.131909966469, -0.0905092954636, -0.0541441440582, -0.0217643976212, -0.0161575078964, -0.0160315036774, 0.0273603200912, 0.0574444532394, 0.103498339653, 0.175806283951, 0.173152208328, 0.0834318399429, -0.092777967453, -0.247517108917, -0.320336461067, -0.362222909927, -0.345616459846, -0.294577121735, -0.220817446709, -0.0772260427475, 0.0768678188324, 0.102220535278, 0.0813870429993, 0.0716757774353, 0.0068963766098, -0.031445145607, -0.0645349025726, -0.0998678207397, -0.115576267242, -0.086575627327, -0.0114878416061, 0.0246556997299, 0.0771030187607, 0.192587375641, 0.275769948959, 0.249179959297, 0.254719018936, 0.323388457298, 0.365169405937, 0.346722006798, 0.266092061996, 0.214153647423, 0.145164370537, 0.0282461643219, -0.0550626516342, -0.0948578119278, -0.108343601227, -0.0976521968842, -0.114726662636, -0.108277201653, -0.0511562824249, -0.0115391016006, 0.0129716396332, 0.0304551124573, 0.0464551448822, 0.0342707633972, 0.0549466609955, 0.163325071335, 0.24224793911, 0.187615156174, 0.111795544624, 0.0935207605362, 0.0949238538742, 0.11606824398, 0.141341924667, 0.175924301147, 0.201873064041, 0.230692744255, 0.257661700249, 0.266361117363, 0.217747569084, 0.0571969747543, -0.0890778303146, -0.129863858223, -0.109778046608, -0.0454210042953, -0.00962626934052, -0.0396602153778, -0.0233778953552, 0.0632855892181, 0.118798136711, 0.107611656189, 0.0783721208572, 0.0523167848587, 0.0216906070709, -0.033225774765, -0.113774418831, -0.150579452515, -0.145341515541, -0.183643817902, -0.219939112663, -0.196112990379, -0.152510166168, -0.102192163467, -0.0686645507812, -0.0712797641754, -0.0844314098358, -0.0755282640457, -0.0499291419983, -0.023989200592, 0.0136096477509, 0.0475459098816, 0.0244779586792, -0.0446070432663, -0.0887378454208, -0.118801593781, -0.168254494667, -0.188887357712, -0.1672488451, -0.188294529915, -0.246451020241, -0.257559895515, -0.257031798363, -0.321408867836, -0.418790817261, -0.464952349663, -0.444991707802, -0.402468323708, -0.369829773903, -0.333155989647, -0.281962871552, -0.212892770767, -0.106101632118, 0.0231850147247, 0.143889904022, 0.229212999344, 0.268185853958, 0.265090227127, 0.251233816147, 0.234152317047, 0.185766339302, 0.150352597237, 0.146755576134, 0.142946958542, 0.161803603172, 0.210229277611, 0.235645055771, 0.230431318283, 0.222740054131, 0.197896838188, 0.162182688713, 0.135030031204, 0.138640642166, 0.178285121918, 0.18684566021, 0.181724429131, 0.215478301048, 0.236952066422, 0.233609080315, 0.225613355637, 0.192869305611, 0.147177815437, 0.125324726105, 0.111914992332, 0.0572109222412, -0.0219846963882, -0.049663066864, -0.0380041599274, -0.0406819581985, -0.0481338500977, -0.0336114168167, 0.00156092643738, 0.0349247455597, 0.0621819496155, 0.0560759305954, 0.0230574607849, -0.015040397644, -0.0586739778519, -0.0641393661499, -0.0332757234573, -0.0237331390381, -0.0518698692322, -0.0622581243515, -0.020077586174, 0.033500790596, 0.0187220573425, -0.0455694198608, -0.0547089576721, -0.0134671926498, 0.00375139713287, -0.0154423713684, -0.0156909227371, -0.000412464141846, 0.0142827033997, 0.048623919487, 0.0860263109207, 0.0892833471298, 0.0497829914093, 0.02729845047, 0.0252348184586, -0.00888752937317, -0.0626990795135, -0.0733869075775, -0.0204157829285, 0.0289169549942, 0.0286276340485, 0.000645995140076, -0.0211623907089, -0.0234845876694, -0.0204062461853, -0.0253423452377, -0.0307157039642, -0.0521181821823, -0.0959683656693, -0.109752416611, -0.111851811409, -0.13977432251, -0.120092511177, -0.033278465271, 0.0258283615112, 0.0256539583206, 0.0244534015656, 0.0276889801025, 0.0179266929626, -0.00349307060242, -0.038104057312, -0.0522675514221, -0.0341384410858, -0.0132089853287, 0.0151813030243, 0.0612938404083, 0.078938126564, 0.0579288005829, 0.0522159337997, 0.0759081840515, 0.0980989933014, 0.0983681678772, 0.082576751709, 0.100293278694, 0.147679209709, 0.151752352715, 0.12836933136, 0.120663642883, 0.117405056953, 0.094834446907, 0.0770245790482, 0.0673829317093, 0.0457669496536, 0.0543355941772, 0.0747513771057, 0.0679701566696, 0.0615832805634, 0.0871274471283, 0.109827756882, 0.112496256828, 0.140894770622, 0.159553408623, 0.143898248672, 0.133523106575, 0.127350687981, 0.11833178997, 0.127085089684, 0.139707922935, 0.128604531288, 0.121683120728, 0.112350940704, 0.0898061990738, 0.104160666466, 0.125478029251, 0.0837721824646, 0.0290728807449, 0.0298305749893, 0.0531919002533, 0.0680649280548, 0.102541089058, 0.161481738091, 0.16373705864, 0.118792891502, 0.0967835187912, 0.0944882631302, 0.111966371536, 0.0865253210068, 0.0829125642776, 0.130622506142, 0.126265048981, 0.066818356514, -0.0150990486145, -0.0306688547134, -0.0207773447037, 0.00242865085602, 0.0605936050415, 0.0429068803787, 0.0580489635468, 0.151015043259, 0.14868927002, 0.115054368973, 0.0717574357986, -0.0341346263885, -0.0830454826355, -0.0396180152893, -0.021174788475, -0.153271913528, -0.239606380463, -0.177180528641, -0.194249629974, -0.231838941574, -0.167630314827, -0.131815671921, -0.131278753281, -0.134327292442, -0.226234793663, -0.2729575634, -0.187339305878, -0.117655873299, -0.146949529648, -0.206521272659, -0.262271046638, -0.320153713226, -0.279294013977, -0.186003446579, -0.216869235039, -0.260317325592}, {0.0, 1.19209289551e-07, 9.53674316406e-07, 2.26497650146e-06, 6.07967376709e-06, 1.07288360596e-05, 1.90734863281e-05, 2.82526016235e-05, -0.000284433364868, -0.00181841850281, -0.00404036045074, -0.000939607620239, 0.00548446178436, 0.00154948234558, -0.0150858163834, -0.0405277013779, -0.0170131921768, 0.0581567287445, 0.0611081123352, 0.0290613174438, 0.0249372720718, 0.0136585235596, 0.0163425207138, 0.0183749198914, 0.000351905822754, -0.0562869310379, -0.0847504138947, -0.0670050382614, -0.0660216808319, -0.0204875469208, 0.0253969430923, 0.0438320636749, 0.0788244009018, 0.0609411001205, 0.00142157077789, -0.0458424091339, -0.0360352993011, 0.0507380962372, 0.0561401844025, -0.032359957695, -0.0762777328491, -0.0406677722931, 0.0483047962189, 0.0534557104111, 0.0114438533783, 0.047042131424, 0.0549479722977, 0.0223340988159, 0.0309567451477, 0.0167764425278, -0.0487298965454, -0.0872447490692, -0.0673480033875, -0.0317034721375, 0.022375702858, 0.0488178730011, -0.0378068685532, -0.0806806087494, 0.00269675254822, 0.0452901124954, -0.0434898138046, -0.135106563568, -0.0751591920853, 0.0172132253647, 0.000269055366516, -0.06276512146, -0.0458401441574, 0.00583899021149, -0.00166249275208, 0.00452983379364, 0.0156536102295, -0.03449010849, -0.0789697170258, -0.0300331115723, 0.0215531587601, -0.014601111412, -0.0183132886887, 0.0388976335526, 0.0318948030472, -0.0102466344833, -0.0329847335815, -0.0489238500595, -0.0678651332855, -0.106956243515, -0.0828790664673, 0.0167622566223, 0.0569086074829, -0.0149880647659, -0.0349942445755, 0.00654685497284, -0.0317544937134, -0.107266306877, -0.111013293266, 0.00904870033264, 0.0486222505569, -0.0460566282272, -0.0796095132828, -0.0232881307602, -0.00454318523407, -0.0962743759155, -0.058845281601, 0.103641748428, 0.0968517065048, 0.0459680557251, 0.0395781993866, -0.0382100343704, -0.0569443702698, -0.0352821350098, -0.0295528173447, 0.0214536190033, -0.0127643346786, -0.0899584293365, -0.00116407871246, 0.132127642632, 0.084562420845, 0.00866079330444, 0.0475641489029, 0.0765109062195, 0.0622664690018, 0.0562746524811, 0.0255446434021, -0.0372357368469, -0.0450986623764, 0.0230967998505, 0.0919142961502, 0.0842709541321, 0.0152244567871, -0.0308192968369, -0.0282647609711, 0.0385298728943, 0.097479224205, 0.0367586612701, -0.000820159912109, 0.0901191234589, 0.170780777931, 0.177416324615, 0.137837529182, 0.0544457435608, -0.0356534719467, -0.0479224920273, 0.0318516492844, 0.105807185173, 0.120500683784, 0.108735799789, 0.120969414711, 0.111375212669, -0.000999331474304, -0.0939314365387, -0.0832600593567, -0.0306129455566, 0.0410190820694, 0.0898066759109, 0.0730932950974, 0.020840883255, 0.00864779949188, 0.057555437088, 0.0828688144684, 0.0620877742767, 0.0716317892075, 0.0343607664108, -0.0571746826172, -0.035356760025, 0.0695893764496, 0.0750497579575, -0.0156222581863, -0.0246486663818, 0.0270652770996, 0.00971651077271, -0.0472379922867, -0.0633101463318, -0.0582149028778, -0.1038864851, -0.194764018059, -0.207269787788, -0.0944820642471, 0.000413298606873, 0.0193418264389, 0.0691826343536, 0.116334795952, 0.0113555192947, -0.129897117615, -0.129679322243, -0.075590133667, -0.112520337105, -0.171551823616, -0.151908278465, -0.106775522232, -0.0917410850525, -0.0828835964203, -0.0511159896851, -0.0201301574707, -0.0207387208939, -0.0379202365875, -0.00459241867065, 0.0325990915298, 0.0502078533173, 0.120794296265, 0.190678238869, 0.144875526428, 0.00758159160614, -0.12455368042, -0.238565444946, -0.3154296875, -0.325667738914, -0.297611951828, -0.249672174454, -0.120938181877, 0.0709567070007, 0.221274375916, 0.287482619286, 0.288263320923, 0.261010050774, 0.218751907349, 0.124433517456, -0.0246541500092, -0.129713892937, -0.126839756966, -0.0903440713882, -0.0924953222275, -0.0747730731964, 0.000419974327087, 0.0812110900879, 0.0854322910309, 0.0535516738892, 0.0856635570526, 0.151977777481, 0.199275016785, 0.22236084938, 0.225029706955, 0.198295712471, 0.152689099312, 0.0849547386169, 0.0166128873825, -0.0106012821198, -0.00878942012787, -0.0614334344864, -0.124426484108, -0.0821034908295, -0.0441224575043, -0.0630667209625, -0.0754957199097, -0.0523163080215, -0.0232968330383, -0.0168722867966, 0.0322142839432, 0.0515093803406, -0.031996011734, -0.0938304662704, -0.0806403160095, -0.062096118927, -0.0597383975983, -0.0138971805573, 0.0584894418716, 0.0889142751694, 0.117195248604, 0.179787635803, 0.243271589279, 0.253578305244, 0.20599758625, 0.146553277969, 0.105143904686, 0.0814113616943, 0.0559048652649, 0.0155752897263, -0.0440500974655, -0.0506972074509, 0.051082611084, 0.113937735558, 0.0444060564041, -0.0325226783752, -0.0525566339493, -0.0806400775909, -0.129501342773, -0.173404574394, -0.198791384697, -0.159120321274, -0.0891497135162, -0.0292555093765, 0.0292551517487, 0.0699725151062, 0.0989569425583, 0.117391228676, 0.118550300598, 0.0957727432251, 0.0873470306396, 0.0966744422913, 0.0684069395065, 0.0156527757645, -0.0123044252396, -0.0452448129654, -0.129007935524, -0.193188667297, -0.196668744087, -0.191532254219, -0.207711696625, -0.205305576324, -0.184805750847, -0.192644476891, -0.170293927193, -0.122241139412, -0.153588533401, -0.227054476738, -0.235806584358, -0.224555850029, -0.249373912811, -0.276501893997, -0.291957974434, -0.267180204391, -0.226834893227, -0.166883826256, -0.0644804239273, 0.0228657722473, 0.10956120491, 0.169780254364, 0.184784293175, 0.198258757591, 0.203212976456, 0.192295074463, 0.178003549576, 0.184361457825, 0.187739014626, 0.218670606613, 0.281817793846, 0.291140079498, 0.265534520149, 0.241701483727, 0.212542295456, 0.173311591148, 0.124453663826, 0.0969718694687, 0.112583994865, 0.117602109909, 0.0988103151321, 0.111392259598, 0.130093574524, 0.126163482666, 0.1148416996, 0.0868505239487, 0.0594708919525, 0.0680602788925, 0.080148935318, 0.0327546596527, -0.0431668758392, -0.0586496591568, -0.037531375885, -0.0546365976334, -0.0844445228577, -0.0922394990921, -0.0977514982224, -0.0941277742386, -0.0828161239624, -0.0805189609528, -0.0910425186157, -0.114775061607, -0.139451265335, -0.150893449783, -0.123095273972, -0.0866711139679, -0.096589922905, -0.134897351265, -0.12737095356, -0.0728754997253, -0.0608561038971, -0.0828922986984, -0.0696986913681, -0.0354330539703, -0.0311689376831, -0.0480697154999, -0.052140712738, -0.0345058441162, -0.00163066387177, 0.0402863025665, 0.0859485864639, 0.0848761796951, 0.0353370904922, 0.0283695459366, 0.0567409992218, 0.0446115732193, -0.00350391864777, -0.0269860029221, 0.0116468667984, 0.0689945220947, 0.103973150253, 0.105943441391, 0.0704308748245, 0.0445065498352, 0.0517021417618, 0.0513691902161, 0.0327147245407, 0.0145680904388, -0.0160201787949, -0.0490015745163, -0.0482045412064, -0.0505193471909, -0.066367149353, -0.0242944955826, 0.0382577180862, 0.0610526800156, 0.0908187627792, 0.0951710939407, 0.0507842302322, 0.0394096374512, 0.0453553199768, 0.0216361284256, 0.0144431591034, 0.0606913566589, 0.100661754608, 0.0907697677612, 0.0804347991943, 0.0843896865845, 0.0724341869354, 0.0692756175995, 0.104802727699, 0.111733078957, 0.0757051706314, 0.0882995128632, 0.143476009369, 0.154353499413, 0.124678611755, 0.123013019562, 0.133461356163, 0.111459732056, 0.0883343219757, 0.087534070015, 0.0576055049896, 0.0120983123779, 0.0275112390518, 0.068131685257, 0.0802036523819, 0.0772593021393, 0.0758391618729, 0.0755889415741, 0.0764381885529, 0.0797604322433, 0.0785938501358, 0.0754408836365, 0.062119603157, 0.0531893968582, 0.0751323699951, 0.0857194662094, 0.0624952316284, 0.0503597259521, 0.0636609792709, 0.0509999990463, 0.00193405151367, 0.0368366241455, 0.138360381126, 0.116444349289, 0.0589332580566, 0.0897933244705, 0.113295674324, 0.122120857239, 0.125940322876, 0.0771644115448, -0.0278371572495, -0.030011177063, 0.0540796518326, 0.0553719997406, 0.0323385000229, -0.0508583784103, -0.0985978841782, -0.0346404314041, -0.0773460865021, -0.163436293602, -0.127063035965, -0.0750198364258, -0.0853251218796, -0.067889213562, 0.030174612999, 0.0951323509216, -0.0132417678833, -0.10206091404, -0.0260002613068, 0.0137438774109, -0.0495629310608, -0.0932512283325, -0.042907834053, -0.00833654403687, -0.037059545517, -0.0694019794464, -0.113046765327, -0.12512087822, -0.0994935035706, -0.107483506203, -0.118926644325, -0.0743587017059, -0.0604677200317, -0.137898921967, -0.171068549156, -0.0921355485916, -0.0877237319946, -0.151871562004, -0.211732745171, -0.23158633709, -0.179649114609, -0.210982203484, -0.265351176262, -0.203472614288, -0.0869618654251, -0.141501784325}};

} // end namespace