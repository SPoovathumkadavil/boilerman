
#import "./template.typ": template

#show: doc => template(
  title: [|||title|||],
  authors: ("Saaleh Poovathumkadavil",),
  doc,
)

