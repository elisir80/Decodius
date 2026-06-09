from PIL import Image, ImageDraw, ImageFilter
S=256
img=Image.new("RGBA",(S,S),(0,0,0,0))
d=ImageDraw.Draw(img)
# sfondo arrotondato scuro (tema neon scuro)
r=44
d.rounded_rectangle([6,6,S-6,S-6], radius=r, fill=(10,16,28,255))
d.rounded_rectangle([6,6,S-6,S-6], radius=r, outline=(28,210,210,90), width=3)
# onde radio concentriche (broadcast) - layer glow
glow=Image.new("RGBA",(S,S),(0,0,0,0))
gd=ImageDraw.Draw(glow)
cx,cy=S//2, S//2+18
cols=[(0,255,220),(0,220,255),(70,160,255)]
for i,rad in enumerate([34,66,98]):
    bbox=[cx-rad,cy-rad,cx+rad,cy+rad]
    # archi rivolti verso l'alto (segnale che si propaga)
    gd.arc(bbox, start=205, end=335, fill=cols[i%3], width=12)
# punto trasmettitore
gd.ellipse([cx-11,cy-11,cx+11,cy+11], fill=(180,255,245,255))
glow2=glow.filter(ImageFilter.GaussianBlur(7))
img=Image.alpha_composite(img, glow2)   # alone
img=Image.alpha_composite(img, glow)    # linee nitide
out_ico="C:/Users/IU8LMC/decodius/decodius.ico"
img.save(out_ico, sizes=[(16,16),(24,24),(32,32),(48,48),(64,64),(128,128),(256,256)])
img.save("C:/Users/IU8LMC/decodius/decodius_preview.png")
print("creato:", out_ico)
