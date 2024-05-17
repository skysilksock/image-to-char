import './style.css'
import { uploadPicture } from './js/upload.ts'


uploadPicture(document.querySelector<HTMLButtonElement>('#card')!)

