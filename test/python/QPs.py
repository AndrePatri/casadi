# %%
import pandas as pd

is_QP = lambda c: c[0] == 'Q' and c[1] in "UXBL"
sif = pd.read_csv('sif.csv')
print(sif)

QPs_df = sif[[is_QP(c) for c in sif.classification]]
print(QPs_df)
QPs = set(QPs_df.name)
selection = {
    "3PK", "A4X12", "A5ESSNDL", "A5NSDSDM", "A5NSSNSM", "A5NSSSSL", "ACOPP14",
    "ACOPP30", "ACOPR14", "AIRCRFTA", "AIRPORT", "ALLINITA", "ALLINITC",
    "ALSOTAME", "ANTWERP", "AVGASA", "AVGASB", "AVION2", "BATCH", "BIGGSC4",
    "BRITGAS", "BT13", "C-RELOAD", "CANTILVR", "CBS", "CLEUVEN7", "CONCON",
    "CORE2", "CRESC50", "DALLASM", "DALLASS", "DECONVBNE", "DECONVC",
    "DECONVNE", "DECONVU", "DEGENLPA", "DEGENLPB", "DEMBO7", "DISC2", "DISCS",
    "DNIEPER", "DUAL1", "DUAL2", "DUAL3", "DUAL4", "DUALC1", "DUALC2",
    "DUALC5", "DUALC8", "EQC", "ERRINBAR", "EXPLIN", "EXPLIN2", "EXPQUAD",
    "FCCU", "FEEDLOC", "FERRISDC", "FLETCHER", "FLOSP2TM", "GAUSSELM",
    "GILBERT", "GOULDQP1", "GOULDQP2", "GOULDQP3", "GRIDGENA", "GRIDNETA",
    "GRIDNETI", "GROUPING", "HADAMARD", "HANGING", "HARKERP2", "HATFLDH",
    "HELSBY", "HIE1327D", "HIE1372D", "HIMMELBI", "HIMMELBJ", "HIMMELBK",
    "HIMMELP1", "HIMMELP2", "HIMMELP3", "HIMMELP4", "HIMMELP5", "HIMMELP6",
    "HOLMES", "HONG", "HS101", "HS102", "HS103", "HS104", "HS105", "HS106",
    "HS107", "HS108", "HS109", "HS110", "HS111", "HS112", "HS114", "HS116",
    "HS117", "HS118", "HS119", "HS13", "HS15", "HS16", "HS17", "HS18", "HS19",
    "HS2", "HS20", "HS21", "HS21MOD", "HS23", "HS24", "HS25", "HS25NE",
    "HS2NE", "HS3", "HS30", "HS31", "HS32", "HS33", "HS34", "HS35", "HS35I",
    "HS35MOD", "HS36", "HS37", "HS38", "HS3MOD", "HS4", "HS41", "HS44",
    "HS44NEW", "HS45", "HS5", "HS53", "HS54", "HS55", "HS57", "HS59", "HS60",
    "HS62", "HS63", "HS64", "HS65", "HS66", "HS67", "HS68", "HS69", "HS70",
    "HS71", "HS72", "HS73", "HS74", "HS75", "HS76", "HS76I", "HS80", "HS81",
    "HS83", "HS84", "HS85", "HS86", "HS87", "HS93", "HS95", "HS96", "HS97",
    "HS98", "HS99", "HS99EXP", "HUBFIT", "HUES-MOD", "HUESTIS", "HVYCRASH",
    "HYDROELL", "HYDROELM", "HYDROELS", "INTEGREQ", "JANNSON3", "JANNSON4",
    "JJTABEL3", "JUNKTURN", "KISSING2", "KTMODEL", "LAKES", "LAUNCH",
    "LEAKNET", "LEUVEN7", "LEWISPOL", "LIN", "LINCONT", "LINSPANH", "LOADBAL",
    "LOOTSMA", "LOTSCHD", "LSNNODOC", "LSQFIT", "LUKVLI5", "MANNE", "MARINE",
    "MATRIX2", "MCONCON", "MESH", "MINC44", "MINPERM", "MINSURFO", "MISTAKE",
    "MODEL", "MPC16", "MRIBASIS", "NASH", "NGONE", "NINE12", "NINE5D",
    "NINENEW", "NUFFIELD", "NYSTROM5", "ODFITS", "OSORIO", "PFIT1", "PFIT2",
    "PFIT3", "PFIT4", "PORTFL1", "PORTFL2", "PORTFL3", "PORTFL4", "PORTFL6",
    "PRIMAL1", "PRIMAL2", "PRIMAL3", "PRIMAL4", "PRIMALC1", "PRIMALC2",
    "PRIMALC5", "PRIMALC8", "PRODPL0", "PRODPL1", "QC", "QCNEW", "QPCBLEND",
    "QPCSTAIR", "QPNBLEND", "READING7", "RES", "RK23", "ROBOT", "ROTDISC",
    "S365", "S365MOD", "S368", "SCOND1LS", "SMBANK", "SMMPSF", "SPANHYD",
    "STNQP2", "SUPERSIM", "SWOPF", "SYNTHES1", "SYNTHES2", "SYNTHES3",
    "TABLE1", "TRUSPYR1", "TRUSPYR2", "TRY-B", "TWIRISM1", "TWOBARS",
    "WACHBIEG", "WATER", "YORKNET", "ZAMB2-10", "ZAMB2-11", "ZAMB2-8",
    "ZAMB2-9", "ZECEVIC2", "ZECEVIC3", "ZECEVIC4", "ZIGZAG", "ZY2"
}
sel_no_QP = selection.difference(QPs)
print(len(sel_no_QP))
print('"' + '"\n"'.join(sorted(sel_no_QP)) + '"')
# %%