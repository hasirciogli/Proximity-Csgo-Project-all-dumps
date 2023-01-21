﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OurCryptercSharp
{
    internal class Program
    {
        static void Main(string[] args)
        {
            ProcCr pc = new ProcCr();

            pc.DeCrypt("4314559035512452824091125792305519553230621256518572005352309813526185970309724032125721853911094340811459918596125192203812582230150053523024145890357104572220951357018538070733603912513100891258626047125291005924577260761258903523195753806712586100361259535018125920354511094360341251118596125713403613533100930306524055145830352219518370421457518593045462207113538185761109223041125141007612572260291251123055045302402312536100841956937022145791857300554230641359018575215493705612543035741254226018145780357721515220581352103542005353602713514185540459422094135541858221599260531259010027125472605813587185530856024063145681851219545220521453003563085773504212559035271952535023125441855324512340211356118553005822405514563035551958133042125621004200566230241258003527045903301312524100601252026065135631001107030240961258710095195503806013524100950853423039125650353619514340781253203511005663409813513100110052423038135341006900532360201459718520045462202013587185500707526046125871858307088340641357910062005862605512577035671958436025135771005908578330531259003572215322404312536185570854134035125451851412580260921252623090195863304114591035310458738013135201851004584380481258310090245712604212569230401258324068125381009519557350571354003558085592306312580035170308433097125780356312547260111359003570215282204313534100650057035071125940356504556220521352018523085953504612596100161259726076145471859721561240291453118536195723701712542185370857635075125210354312519370291257518589125323407612575230932455226084125442309419562330471456918542005932609713563185212153535087125882309521578260731451203594125412407112525100491951534081135602301604584260951252303510125383705912531100532455434027125841857607023220161256510042005282205112540100230459122065135251851203042380811251703594125183405214593035460458322060125531857519512360481258023037125923504212515035390308134070125381857512520340671357918580110352601312564230311952034094145180357500539330421355518574125413307312559100252159826052135670359900546240111254723087195312303913520230130052423091135571856521553350331256210094045313409214519185701256822047125441009500576360281355010087045972303413563185810708324046125331852007041340491357003524195822606912543035411955422058135620354012515370351251903543110922204812597185940856834011135542306300515240451451203596195583606914562185690054537039135241858519510360351254823068195702607112573185821259224072125771005019573350311351323033005272309013569185751958522038125431856708528340731354718599215132301912511230680051236078125300358104558220841351818526070702403912573100201257026038125771854621593260451251623075005283305313579185740859835043125390354708526360941252518518125663404114565035251955126059125562305419575240641354203575005133704213566185880706224096125361008312549260141455518526085322403513543035151952638076125810354404564370761359218596070682606212515035550056134060125312305504541230671355610080005403309213544035130451322096135521856808572350131256410023125842603312546100680056424087125831002919598350501353023088125383603012545035511956424033125861854308599340621256118559030282603212573230841957038012135932306104529220181351918528030393604112543100850857126054135721852503033240481251910042195983305712530230610453426098125710359924523230851257918517110793406812540185311958422097135251008500585380701457918572045482301213574185750702038014125341852000535260411357103535070692602014578035431957822047125521858608579220231252803581195503702312543185381258434038135100354108595240241259103593005172206313585100480054526056135691854021588350791252323016195302604614519035370059824049125441009119545330161257623056045163705613527185610458437090125261859108562340611254418569005852309214593035340051122085125921858304591220461353818558195322205712517035911253234086135900359419589240441257618560005633403612592035741256534048125780353121542380111256418569085483407214514185752457222079125192306800563220281357623029005183605612556035922459337018125621007621542260871256518537125382404212537100581953035052135301858804519370921352818532110102406512585035420303726026125471851808517220981359110096005303504912515035380455923050135601855024537240621254503575125823405113584100282152626084125460354819549220981354303555085453301112535035551951826014125701851512524340371258218541215242404914519035701957338010125331857504530220371355618577070283707312586230341259426011135692306511085240271252410057195233405414580035580056823031135751857204523330421251418576110763405612522185490457023024135191005300541350611354903559045852203513535185262155023095125991009412586260731256410019110702608513543230290053134042145680359808531350881258603580245823709412559185501257234052135212302500514260741252423062195952406014534035520851124032135871857724579360551255510064215402606312544100610303224072125491002819572330521453703528045153702813543185691957423084125660359900568340151458603576070802203712562100170051237056125242303704581220231354218591070463606312548185430708234068145261855004571260621351603560195252401412516035671254936043125740352719588360281254118576085533409813587185961254126087125722308319557360781356503568005853709813537185831108338011125402302803051260801357910042215242403912561100251952733083135931851400512230121357018571110122405712527100402458234064145411854000513220871352310059005452301914587185820459023022135881851619547380601254810081125182602313560100532155624052125701857200528230841459103528085933302712535035580309123087125801859412568340281256110063245962402712538035590059523075145450353600546260131359018520110483302812572100231259026026125352302011089240571253210042195483402214539185240452426048125820354724572220951251803534005873403313529185651953123019135902302200558350831356118594045232202113530185642451023057125690356012588340711356403520125872609914535035331955822032125832309212591350401259403550215973609512589185500859534091135822308024559240781257903521005173508312543230100458738066135561859003022370881259910088215392607912539185640058224040125181007719548340971456303580045372607612524035521952137039125611858604530260331354323046005522208213551100140057338082135561008004515230241358918576245103702812542100871251426050145170359604540260711258203559195233508814555185210859523016125260352804518370891254818547125703406712569100611103524078145260354319529360941359523043005282606213593185591955422098125252304103043260221359818581085162408412576100871956738059145460353400551230891356218556215132201112515185490454726040125521856607011230471259623092005453506314534185400458722015135751859308591260781252818558005202603113597185250309026015125890351019539330131451503584085123501712582035860708724092125321855024511340411253710055195992403114568035411951723098145260355604529220491351218546070363504512558100142451026013145871853804593240711253110022195452407712566100320858123026125110352112575330271254403558005553404613574230790857823024135831859200525370331359818563045122207713570185460703837070125511854107079340751359310056215532607112535035931952438030125631002112567330991253003523125153507212519185910855234076135712306719580260311258523072195723803912560230450055133038135531852607038380381255610091085862607614557035700853424059125381005919584380991359803527005652307613594185880309635018125470354824510340891259510096045392201013520100110057334065145650355804580220811357718527030442206612527185500701734094125712305204541240181252310095195773309112564185870855622038125520357312560380121258718578085683407513569185670304124053125340351700561330731353710061005322602713515185531106422064125252303512581260141451118522110162406612523100131959033070135281859108543350981252103546045292206812540100410307326029145631852900523220461353523075005943808012525005402707627015", out string sa);

            

            Console.WriteLine(sa);
            Console.ReadKey();
        }
    }
}