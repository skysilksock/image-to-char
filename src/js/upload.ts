
const preUrl = "http://localhost:5003/api";

export function uploadPicture(element: HTMLButtonElement) {
    element.addEventListener('click', () => {
        // 创建链接使用户上传图片
        const input: HTMLInputElement = document.createElement('input');
        input.type = 'file';
        input.accept = 'image/*';
        input.click();
        input.onchange = () => {
            const file: File | null = (input.files as FileList)[0];
            const formData = new FormData();
            formData.append("file", file);
            console.log(formData, file);
            fetch(preUrl + '/get-char', {
                method: 'POST',
                body: formData,
            })
                .then((response) => response.json())
                .then((data) => {
                    if (data.status == 'ok') {
                        console.log(data.data);
                        document.querySelector<HTMLDivElement>('#result')!.innerText = data.data;
                    }
                    else {
                        document.querySelector<HTMLDivElement>('#result')!.innerText = '上传失败';
                    }
                })
                .catch((error) => {
                    console.error('Error:', error);
                });
        };
    });
}